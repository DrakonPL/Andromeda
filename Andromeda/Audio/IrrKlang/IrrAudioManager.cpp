#include <Andromeda/Audio/IrrKlang/IrrAudioManager.h>
#include <Andromeda/Audio/IrrKlang/IrrSound.h>



namespace Andromeda
{
	namespace Audio
	{
		bool IrrAudioManager::Init()
		{
			_engine = createIrrKlangDevice();

			if (!_engine)
			{
				return false;
			}

			return true;
		}

		Sound* IrrAudioManager::GetSound(std::string name)
		{
			IrrSound* sound = new IrrSound(name);
			sound->SetEngine(_engine);

			return sound;
		}		
	}
}
