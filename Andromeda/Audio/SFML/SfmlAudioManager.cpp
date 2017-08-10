#include <Andromeda/Audio/SFML/SfmlAudioManager.h>
#include <Andromeda/Audio/SFML/SfmlSound.h>
#include <Andromeda/Utils/Logger.h>

namespace Andromeda
{
	namespace Audio
	{
		bool SfmlAudioManager::Init()
		{
			Utils::Logger::Instance()->Log("AudioManager - Init\n");

			return true;
		}

		Sound* SfmlAudioManager::GetSound(std::string name)
		{
			SfmlSound* sound = new SfmlSound(name);
			return sound;
		}
	}
}
