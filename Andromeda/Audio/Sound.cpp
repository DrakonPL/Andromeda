#include <Andromeda/Audio/Sound.h>

namespace Andromeda
{
	namespace Audio
	{
		Sound::Sound(std::string name)
		{
			_name = name;
			_volume = 1.0f;
		}

		Sound::~Sound()
		{

		}

		void Sound::SetLoop(bool looped)
		{
			_looped = looped;
		}

		void Sound::SetVolume(float volume)
		{
			_volume = volume;

			UpdateVolume();
		}

		float Sound::GetVolume()
		{
			return _volume;
		}
	}
}

