#include <Andromeda/Video/FFmpeg/FFmpegVideoManager.h>
#include <Andromeda/Video/FFmpeg/FFmpegMovie.h>


namespace Andromeda
{
	namespace Video
	{
		FFmpegVideoManager::FFmpegVideoManager()
		{
			_paStream = 0;
		}

		FFmpegVideoManager::~FFmpegVideoManager()
		{
			if (_paStream != 0)
			{
				Pa_CloseStream(_paStream);
			}
		}

		bool FFmpegVideoManager::Init()
		{
			if (!InitAudio())
			{
				return false;
			}

			return true;
		}

		bool FFmpegVideoManager::InitAudio()
		{
			if (Pa_Initialize() != paNoError)
			{
				return false;
			};
			
			unsigned int numDevices = Pa_GetDeviceCount();
			for (size_t i = 0; i < numDevices; i++)
			{
				const   PaDeviceInfo *deviceInfo = Pa_GetDeviceInfo(i);

				printf("Name                        = %s\n", deviceInfo->name);
				printf("Host API                    = %s\n", Pa_GetHostApiInfo(deviceInfo->hostApi)->name);
			}

			int device = Pa_GetDefaultOutputDevice();

			PaStreamParameters outputParameters;

			//reset all settings
			memset(&outputParameters, 0, sizeof(PaStreamParameters));

			//set options
			outputParameters.channelCount = 2;
			outputParameters.device = device;
			outputParameters.sampleFormat = paFloat32;
			outputParameters.suggestedLatency = Pa_GetDeviceInfo(device)->defaultHighOutputLatency;
			outputParameters.hostApiSpecificStreamInfo = NULL; //See you specific host's API docs for info on using this field

			if (Pa_OpenStream(
				&_paStream,
				0,
				&outputParameters,
				44100, // Sample Rate
				1024,  // Frames per buffer 
				paNoFlag,
				&AudioCallback,
				this) != paNoError)
			{

				return false;
			}

			if (Pa_StartStream(_paStream) != paNoError)
			{
				return false;
			}

			return true;
		}

		int FFmpegVideoManager::AudioCallback(const void *input, void *output,
			unsigned long frameCount,
			const PaStreamCallbackTimeInfo* timeInfo,
			PaStreamCallbackFlags statusFlags,
			void* userData)
		{
			memset(output, 0, frameCount * 8);
			
			FFmpegVideoManager* manager = (FFmpegVideoManager*)userData;

			for (unsigned int i = 0; i < manager->GetMovies().size(); i++)
			{
				if (manager->GetMovies()[i]->IsPlaying() && manager->GetMovies()[i]->HaveAudio())
				{
					manager->GetMovies()[i]->AudioOut((float*)output, frameCount, 2);
				}				
			}

			return 0;
		}

		Movie* FFmpegVideoManager::GetMovie(std::string name)
		{
			FFmpegMovie* movie = new FFmpegMovie(name);

			_movies.push_back(movie);

			return movie;
		}

		Movie* FFmpegVideoManager::GetMovie(std::string name, glm::vec2 position, glm::vec2 size)
		{
			FFmpegMovie* movie = new FFmpegMovie(name, position,size);

			_movies.push_back(movie);

			return movie;
		}

		void FFmpegVideoManager::Update(float dt)
		{
			for (unsigned int i = 0; i < _movies.size(); i++)
			{
				_movies[i]->Update(dt);
			}
		}
	}
}