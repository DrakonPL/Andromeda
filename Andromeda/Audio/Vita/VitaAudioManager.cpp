#include <Andromeda/Audio/Vita/VitaAudioManager.h>
#include <Andromeda/Audio/Vita/VitaSound.h>
#include <Andromeda/Utils/Logger.h>


SceUID AudioThreads[AUDIO_CHANNELS], Audio_Mutex, NewTrack_Mutex;
DecodedMusic* new_track = NULL;
bool initialized = false;
bool availThreads[AUDIO_CHANNELS];
std::unique_ptr<AudioDecoder> audio_decoder[AUDIO_CHANNELS];
volatile bool mustExit = false;
uint8_t ids[] = { 0, 1, 2, 3, 4, 5, 6 ,7 }; // Change this if you edit AUDIO_CHANNELS macro


// Audio thread code
static int audioThread(unsigned int args, void* arg)
{
	// Getting thread id
	uint8_t* argv = (uint8_t*)arg;
	uint8_t id = argv[0];

	// Initializing audio port
	int ch = sceAudioOutOpenPort(SCE_AUDIO_OUT_PORT_TYPE_MAIN, NSAMPLES, 48000, SCE_AUDIO_OUT_MODE_STEREO);
	sceAudioOutSetConfig(ch, -1, -1, -1);
	int vol_stereo[] = { 32767, 32767 };
	sceAudioOutSetVolume(ch, SCE_AUDIO_VOLUME_FLAG_L_CH | SCE_AUDIO_VOLUME_FLAG_R_CH, vol_stereo);

	DecodedMusic* mus;
	for (;;)
	{
		// Waiting for an audio output request
		sceKernelWaitSema(Audio_Mutex, 1, NULL);

		// Setting thread as busy
		availThreads[id] = false;

		// Fetching track
		mus = new_track;
		mus->audioPort = ch;
		mus->audioThread = id;

		//set mus volume
		float vol = 32767.0f * mus->volume;
		int my_vol[] = { vol, vol };
		sceAudioOutSetVolume(ch, SCE_AUDIO_VOLUME_FLAG_L_CH | SCE_AUDIO_VOLUME_FLAG_R_CH, my_vol);

		sceKernelSignalSema(NewTrack_Mutex, 1);

		// Checking if a new track is available
		if (mus == NULL)
		{
			//If we enter here, we probably are in the exiting procedure
			if (mustExit)
			{
				sceKernelSignalSema(Audio_Mutex, 1);
				sceAudioOutReleasePort(ch);
				sceKernelExitDeleteThread(0);
			}
		}

		// Initializing audio decoder
		audio_decoder[id] = AudioDecoder::Create(mus->handle, "Track");
		if (audio_decoder[id] == NULL) continue; // TODO: Find why this case apparently can happen
		audio_decoder[id]->Open(mus->handle);
		audio_decoder[id]->SetLooping(mus->loop);
		audio_decoder[id]->SetFormat(48000, AudioDecoder::Format::S16, 2);

		//int audiotype;
		//int samplerate;
		//AudioDecoder::Format int_format;

		//audio_decoder[id]->GetFormat(samplerate, int_format, audiotype);

		//mus->isStereo = audiotype == 2;

		//uint8_t audio_mode = mus->isStereo ? SCE_AUDIO_OUT_MODE_STEREO : SCE_AUDIO_OUT_MODE_MONO;
		//int nsamples = NSAMPLES / ((audio_mode + 1) << 1);

		//sceAudioOutSetConfig(mus->portNumber, nsamples	, 48000, audio_mode);

		// Initializing audio buffers
		mus->audiobuf = (uint8_t*)malloc(BUFSIZE);
		mus->audiobuf2 = (uint8_t*)malloc(BUFSIZE);
		mus->cur_audiobuf = mus->audiobuf;

		// Audio playback loop
		for (;;)
		{
			// Check if the music must be paused
			if (mus->pauseTrigger || mustExit)
			{
				// Check if the music must be closed
				if (mus->closeTrigger)
				{
					//Andromeda::Utils::Logger::Instance()->NetLog("VitaSoundManager - closeTrigger \n");

					audio_decoder[id].reset();
					if (mus->tempBlock)
					{
						free(mus->audiobuf);
						free(mus->audiobuf2);
						free(mus);
						mus = NULL;
					}
					else
					{
						mus->handle = fopen(mus->filepath, "rb");
						mus->audioThread = 0xFF;
					}

					availThreads[id] = true;

					if (!mustExit) break;
				}

				// Check if the thread must be closed
				if (mustExit)
				{
					//Andromeda::Utils::Logger::Instance()->NetLog("VitaSoundManager - mustExit \n");

					// Check if the audio stream has already been closed
					if (mus != NULL)
					{
						mus->closeTrigger = true;
						continue;
					}

					// Recursively closing all the threads
					sceKernelSignalSema(Audio_Mutex, 1);
					sceAudioOutReleasePort(ch);
					sceKernelExitDeleteThread(0);
				}

				mus->isPlaying = !mus->isPlaying;
				mus->pauseTrigger = false;
			}

			if (mus->isPlaying)
			{
				// Check if audio playback finished
				if ((!mus->loop) && audio_decoder[id]->IsFinished()) mus->isPlaying = false;

				// Update audio output
				if (mus->cur_audiobuf == mus->audiobuf) 
					mus->cur_audiobuf = mus->audiobuf2;
				else 
					mus->cur_audiobuf = mus->audiobuf;

				audio_decoder[id]->Decode(mus->cur_audiobuf, BUFSIZE);

				sceAudioOutOutput(ch, mus->cur_audiobuf);
			}
			else
			{
				// Check if we finished a non-looping audio playback
				if ((!mus->loop) && audio_decoder[id]->IsFinished())
				{
					//Andromeda::Utils::Logger::Instance()->NetLog("VitaSoundManager - finished a non-looping audio \n");

					// Releasing the audio file
					audio_decoder[id].reset();
					if (mus->tempBlock)
					{
						free(mus->audiobuf);
						free(mus->audiobuf2);
						free(mus);
						mus = NULL;
					}
					else
					{
						mus->handle = fopen(mus->filepath, "rb");
						mus->audioThread = 0xFF;
					}
					availThreads[id] = true;
					break;
				}
			}
		}
	}
}

namespace Andromeda
{
	namespace Audio
	{
		bool VitaAudioManager::InitThreads()
		{
			if (!initialized)
			{
				// Creating audio mutexs
				Audio_Mutex = sceKernelCreateSema("Audio Mutex", 0, 0, 1, NULL);
				NewTrack_Mutex = sceKernelCreateSema("NewTrack Mutex", 0, 1, 1, NULL);

				// Starting audio threads
				for (int i = 0; i < AUDIO_CHANNELS; i++) 
				{
					availThreads[i] = true;
					AudioThreads[i] = sceKernelCreateThread("Audio Thread", &audioThread, 0x10000100, 0x10000, 0, 0, NULL);
					int res = sceKernelStartThread(AudioThreads[i], sizeof(ids[i]), &ids[i]);
					if (res != 0)
					{
						Utils::Logger::Instance()->Log("Can't initialize thread: %d\n",i);
						return false;
					}
				}

				initialized = true;
			}

			return true;
		}

		void VitaAudioManager::TerminateThreads()
		{
			if (initialized)
			{
				// Starting exit procedure for audio threads
				mustExit = true;
				sceKernelSignalSema(Audio_Mutex, 1);

				for (int i = 0; i<AUDIO_CHANNELS; i++)
				{
					sceKernelWaitThreadEnd(AudioThreads[i], NULL, NULL);
				}

				mustExit = false;

				// Deleting audio mutex
				sceKernelDeleteSema(Audio_Mutex);

				initialized = false;
			}
		}

		bool VitaAudioManager::Init()
		{
			Utils::Logger::Instance()->Log("AudioManager - Init\n");
			bool state = InitThreads();

			if (state)
			{
				Utils::Logger::Instance()->Log("AudioManager - Init Success\n");
			}

			return state;
		}

		Sound* VitaAudioManager::GetSound(std::string name)
		{
			VitaSound* sound = new VitaSound(name);
			return sound;
		}

		void VitaAudioManager::Play(DecodedMusic* sound)
		{
			// Wait till a thread is available
			bool found = false;
			while (!found)
			{
				for (int i = 0; i<AUDIO_CHANNELS; i++)
				{
					found = availThreads[i];
					if (found) break;
				}
			}

			// Waiting till track slot is free
			sceKernelWaitSema(NewTrack_Mutex, 1, NULL);

			// Passing music to an audio thread
			new_track = sound;
			sceKernelSignalSema(Audio_Mutex, 1);
		}

		void VitaAudioManager::UpdateVolume(DecodedMusic* sound)
		{
			float vol = 32767.0f * sound->volume;
			int my_vol[] = { vol, vol };
			sceAudioOutSetVolume(sound->audioPort, SCE_AUDIO_VOLUME_FLAG_L_CH | SCE_AUDIO_VOLUME_FLAG_R_CH, my_vol);
		}
	}
}
