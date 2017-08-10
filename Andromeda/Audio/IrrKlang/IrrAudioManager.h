#ifndef IrrAudioManager_H
#define IrrAudioManager_H

#include <Andromeda/Audio/AudioManager.h>
#include <string>

#include <irrKlang.h>

using namespace irrklang;

namespace Andromeda
{
	namespace Audio
	{
		class IrrAudioManager : public AudioManager
		{
		private:

			ISoundEngine* _engine;

		public:

			bool Init();
			Sound* GetSound(std::string name);
		};
	}
}

#endif