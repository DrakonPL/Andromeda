#ifndef IrrSound_H
#define IrrSound_H

#include <Andromeda/Audio/Sound.h>
#include <string>

#include <irrKlang.h>
using namespace irrklang;

namespace Andromeda
{
	namespace Audio
	{
		class IrrAudioManager;

		class IrrSound : public Sound
		{
		private:

			ISoundSource* _soundSource;
			ISound* _sound;
			ISoundEngine* _engine;

			void SetEngine(ISoundEngine* engine);

		public:

			IrrSound(std::string name);
			~IrrSound();

			bool IsPlaying();

			bool LoadWav(std::string filePath, bool streaming);
			bool LoadOgg(std::string filePath);

			void UpdateVolume();

			void Play();
			void Stop();
			void Pause();

			friend class IrrAudioManager;
		};
	}
}

#endif
