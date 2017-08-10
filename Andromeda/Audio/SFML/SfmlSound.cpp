#include <Andromeda/Audio/SFML/SfmlSound.h>
#include <Andromeda/FileSystem/FileManager.h>
#include <string>

#include <Andromeda/Audio/SFML/SfmlAudioManager.h>
#include <Andromeda/Utils/Logger.h>

namespace Andromeda
{
	namespace Audio
	{

		SfmlSound::SfmlSound(std::string name): Sound(name)
		{
			_looped = false;
			_volume = 1.0f;

			_music = 0;
			_sound = 0;
		}

		SfmlSound::~SfmlSound()
		{
			if (_music != 0)
			{
				delete _music;
			}

			if (_sound != 0)
			{
				delete _sound;
			}
		}

		bool SfmlSound::IsPlaying()
		{
			return false;
		}

		bool SfmlSound::LoadWav(std::string filePath, bool streaming)
		{
			_filePath = filePath;
			
			if (!_soundBuffer.loadFromFile(filePath))
			{
				Utils::Logger::Instance()->Log("Can't open: %s\n", filePath.c_str());
				return false;
			}				

			_sound = new sf::Sound();
			_sound->setBuffer(_soundBuffer);

			_sound->setVolume(_volume * 100);
			_sound->setLoop(_looped);

			_isSound = true;

			return true;
		}

		bool SfmlSound::LoadOgg(std::string filePath)
		{
			_filePath = filePath;

			_music = new sf::Music();

			if (!_music->openFromFile(filePath))
			{
				Utils::Logger::Instance()->Log("Can't open: %s\n", filePath.c_str());
				return false;
			}

			_music->setVolume(_volume * 100);
			_music->setLoop(_looped);

			_isSound = false;

			return true;
		}
		
		void SfmlSound::UpdateVolume()
		{
			if (_isSound)
			{
				_sound->setVolume(_volume * 100);
			}
			else
			{
				_music->setVolume(_volume * 100);
			}
		}

		void SfmlSound::Play()
		{
			if (_isSound)
			{
				_sound->play();
			}
			else
			{
				_music->play();
			}
		}

		void SfmlSound::Stop()
		{
			if (_isSound)
			{
				_sound->stop();
			}
			else
			{
				_music->stop();
			}
		}

		void SfmlSound::Pause()
		{
			if (_isSound)
			{
				_sound->pause();
			}
			else
			{
				_music->pause();
			}
		}
	}
}

