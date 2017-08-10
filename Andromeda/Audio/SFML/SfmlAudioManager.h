#ifndef SfmlAudioManager_H
#define SfmlAudioManager_H

#include <Andromeda/Audio/AudioManager.h>
#include <string>

namespace Andromeda
{
	namespace Audio
	{
		class SfmlAudioManager : public AudioManager
		{
		private:


		public:

			bool Init();
			Sound* GetSound(std::string name);

		};
	}
}

#endif