#ifndef SfmlSound_H
#define SfmlSound_H

#include <Andromeda/Audio/Sound.h>
#include <SFML/Audio.hpp>
#include <string>

namespace Andromeda
{
	namespace Audio
	{
		class SfmlSound : public Sound
		{
		private:

			sf::Music* _music;

			sf::Sound* _sound;
			sf::SoundBuffer _soundBuffer;

			bool _isSound;

		public:

			SfmlSound(std::string name);
			~SfmlSound();

			bool IsPlaying();

			bool LoadWav(std::string filePath, bool streaming);
			bool LoadOgg(std::string filePath);
			
			void UpdateVolume();

			void Play();
			void Stop();
			void Pause();
		};
	}
}

#endif
