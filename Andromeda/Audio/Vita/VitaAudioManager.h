#ifndef VitaAudioManager_H
#define VitaAudioManager_H

#include <Andromeda/Audio/AudioManager.h>
#include <string>

#include "SharedData.h"


namespace Andromeda
{
	namespace Audio
	{
		class VitaAudioManager : public AudioManager
		{
		private:

			bool InitThreads();
			void TerminateThreads();

		public:

			bool Init();
			Sound* GetSound(std::string name);

			void Play(DecodedMusic* sound);
			void UpdateVolume(DecodedMusic* sound);
		};
	}
}

#endif