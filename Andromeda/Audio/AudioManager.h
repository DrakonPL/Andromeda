#ifndef AudioManager_H
#define AudioManager_H

#include <Andromeda/Audio/Sound.h>
#include <string>

namespace Andromeda
{
	namespace Audio
	{
		class AudioManager
		{
		protected:

			static AudioManager *_audioManager;

		public:

			AudioManager();

			static AudioManager* Instance();

		public:

			virtual bool Init() = 0;
			virtual Sound* GetSound(std::string name) = 0;
		};
	}
}

#endif