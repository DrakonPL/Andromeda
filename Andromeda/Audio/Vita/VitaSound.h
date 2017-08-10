#ifndef VitaSound_H
#define VitaSound_H

#include <Andromeda/Audio/Sound.h>
#include <string>
#include "SharedData.h"

namespace Andromeda
{
	namespace Audio
	{
		class VitaSound : public Sound
		{
		private:

			DecodedMusic* _music;
			

		public:

			VitaSound(std::string name);
			~VitaSound();

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
