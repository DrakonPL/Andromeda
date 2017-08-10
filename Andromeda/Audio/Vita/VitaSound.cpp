#include <Andromeda/Audio/Vita/VitaSound.h>
#include <Andromeda/FileSystem/FileManager.h>
#include <string>

#include <Andromeda/Audio/Vita/VitaAudioManager.h>
#include <Andromeda/Utils/Logger.h>

namespace Andromeda
{
	namespace Audio
	{

		VitaSound::VitaSound(std::string name) : Sound(name)
		{
			_looped = false;
			_volume = 1.0f;
			_music = NULL;
		}

		VitaSound::~VitaSound()
		{

		}

		bool VitaSound::IsPlaying()
		{
			if (_music != NULL)
			{
				return _music->isPlaying;
			}

			return false;
		}

		bool VitaSound::LoadWav(std::string filePath, bool streaming)
		{
			std::string loadName = FileSystem::FileManager::Instance()->GetMainDirPath() + filePath;

			// Opening file and checking for magic
			FILE* f = fopen(loadName.c_str(), "rb");
			if (f == NULL)
			{
				Utils::Logger::Instance()->Log("VitaSound - LoadWav - Can't load: %s\n", loadName.c_str());
				return false;
			}
				

			uint32_t magic;
			fread(&magic, 1, 4, f);
			if (magic != 0x46464952)
			{
				Utils::Logger::Instance()->Log("VitaSound - LoadWav - Wrong magic number\n");
				return false;
			}

			fseek(f, 0, SEEK_SET);

			// Allocating and pushing music block
			_music = (DecodedMusic*)malloc(sizeof(DecodedMusic));
			_music->handle = f;
			_music->isPlaying = false;
			_music->audioThread = 0xFF;
			_music->tempBlock = false;
			sprintf(_music->filepath, "%s", loadName.c_str());

			return true;
		}

		bool VitaSound::LoadOgg(std::string filePath)
		{
			std::string loadName = FileSystem::FileManager::Instance()->GetMainDirPath() + filePath;

			// Opening file and checking for magic
			FILE* f = fopen(loadName.c_str(), "rb");
			if (f == NULL) 
				return false;

			uint32_t magic;
			fread(&magic, 1, 4, f);
			if (magic != 0x5367674f) 
				return false;

			fseek(f, 0, SEEK_SET);

			// Allocating and pushing music block
			_music = (DecodedMusic*)malloc(sizeof(DecodedMusic));
			_music->handle = f;
			_music->isPlaying = false;
			_music->audioThread = 0xFF;
			_music->tempBlock = false;
			sprintf(_music->filepath, "%s", loadName.c_str());

			return true;
		}
		
		void VitaSound::UpdateVolume()
		{
			_music->volume = _volume;

			if (_music->audioThread != 0xFF)
			{
				VitaAudioManager* manager = (VitaAudioManager*)AudioManager::Instance();
				manager->UpdateVolume(_music);
			}
		}

		void VitaSound::Play()
		{
			// Check if the music is already loaded into an audio thread
			if (_music->audioThread != 0xFF) 
			{
				//Utils::Logger::Instance()->NetLog("VitaSound - Play - already loaded: %s\n", _name.c_str());
				return;

				// We create a temporary duplicated and play it instead of the original one
				//DecodedMusic* dup = (DecodedMusic*)malloc(sizeof(DecodedMusic));
				//memcpy(dup, _music, sizeof(DecodedMusic));
				//dup->handle = fopen(dup->filepath, "rb");
				//dup->tempBlock = true;
				//_music = dup;
			}

			//Utils::Logger::Instance()->NetLog("VitaSound - Play - %s\n", _name.c_str());

			// Properly setting music memory block info
			_music->loop = _looped;
			_music->pauseTrigger = false;
			_music->closeTrigger = false;
			_music->isPlaying = true;
			_music->volume = _volume;

			VitaAudioManager* manager = (VitaAudioManager*)AudioManager::Instance();

			manager->Play(_music);
		}

		void VitaSound::Stop()
		{
			//Utils::Logger::Instance()->NetLog("VitaSound - Stop - %s\n", _name.c_str());

			_music->loop = false;
			_music->closeTrigger = true;
			_music->pauseTrigger = true;
		}

		void VitaSound::Pause()
		{
			if (_music->isPlaying)
			{
				_music->pauseTrigger = true;
			}
		}

	}
}

