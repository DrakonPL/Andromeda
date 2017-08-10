#ifndef Sound_H
#define Sound_H

#include <string>

namespace Andromeda
{
	namespace Audio
	{
		class Sound
		{
		protected:

			bool _stream;
			bool _looped;
			bool _loaded;

			std::string _name;
			std::string _filePath;

			float _volume;

		public:

			Sound(std::string name);
			virtual ~Sound();

			bool IsLooped() { return _looped; }
			bool IsStreaming() { return _stream; }
			bool IsLoaded() { return _loaded; }

			std::string GetName() { return _name; }
			std::string GetFilePath() { return _filePath; }

			void SetVolume(float volume);
			float GetVolume();

			void SetLoop(bool state);

			virtual bool IsPlaying() = 0;

			virtual bool LoadWav(std::string filePath, bool streaming) = 0;
			virtual bool LoadOgg(std::string filePath) = 0;

			virtual void UpdateVolume() = 0;

			virtual void Play() = 0;
			virtual void Stop() = 0;
			virtual void Pause() = 0;
		};
	}
}

#endif
