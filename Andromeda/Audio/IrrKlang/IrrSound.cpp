#include <Andromeda/Audio/IrrKlang/IrrSound.h>
#include <Andromeda/FileSystem/FileManager.h>
#include <string>

namespace Andromeda
{
	namespace Audio
	{

		IrrSound::IrrSound(std::string name) : Sound(name)
		{
			_soundSource = 0;
			_looped = false;
			_sound = 0;
			_engine = 0;
		}

		IrrSound::~IrrSound()
		{
			if (_soundSource != 0)
			{
				_engine->removeSoundSource(_soundSource);
				delete _soundSource;
			}
		}

		void IrrSound::SetEngine(ISoundEngine* engine)
		{
			_engine = engine;
		}

		bool IrrSound::IsPlaying()
		{
			if (_sound == 0)
			{
				return false;
			}

			return !_sound->isFinished();
		}

		bool IrrSound::LoadWav(std::string filePath, bool streaming)
		{
			std::string loadName = FileSystem::FileManager::Instance()->GetMainDirPath() + filePath;

			if (streaming)
				_soundSource = _engine->addSoundSourceFromFile(loadName.c_str(), ESM_STREAMING);
			else
				_soundSource = _engine->addSoundSourceFromFile(loadName.c_str(), ESM_NO_STREAMING);

			if (_soundSource == 0)
				return false;

			return true;
		}

		bool IrrSound::LoadOgg(std::string filePath)
		{
			std::string loadName = FileSystem::FileManager::Instance()->GetMainDirPath() + filePath;

			_soundSource = _engine->addSoundSourceFromFile(loadName.c_str());

			if (_soundSource == 0)
				return false;

			return true;
		}

		void IrrSound::UpdateVolume()
		{
			if (_sound != 0)
			{
				_sound->setVolume(_volume);
			}
		}

		void IrrSound::Play()
		{
			if (_soundSource != 0)
			{
				_sound = _engine->play2D(_soundSource, _looped, false, true, true);
				_sound->setVolume(_volume);
			}			
		}

		void IrrSound::Stop()
		{
			if (_sound != 0)
			{
				_sound->stop();
			}			
		}

		void IrrSound::Pause()
		{

		}

	}
}

