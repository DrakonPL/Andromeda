#ifndef Movie_H
#define Movie_H

#include <Andromeda/Graphics/Texture.h>
#include <glm/glm.hpp>
#include <string>

namespace Andromeda
{
	namespace Video
	{
		class VideoManager;
		class Movie
		{
		protected:

			bool _stream;
			bool _looped;
			bool _loaded;
			bool _screenChanged;

			glm::vec2 _srcPosition;
			glm::vec2 _srcSize;

			std::string _name;
			std::string _filePath;

			float _volume;

			Graphics::Texture* _texture;

			Movie(std::string name);
			Movie(std::string name, glm::vec2 position, glm::vec2 size);

		public:

			virtual ~Movie();

			bool IsLooped() { return _looped; }
			bool IsStreaming() { return _stream; }
			bool IsLoaded() { return _loaded; }

			std::string GetName() { return _name; }
			std::string GetFilePath() { return _filePath; }

			void SetVolume(float volume);
			float GetVolume() { return _volume; }

			void SetLoop(bool state);

			Graphics::Texture* GetTexture() { return _texture; }

			virtual void AudioOut(float *output, int bufferSize, int nChannels) = 0;

			virtual bool IsPlaying() = 0;

			virtual bool Load(std::string filePath) = 0;

			virtual void Update(float dt) = 0;

			virtual void Play() = 0;
			virtual void Stop() = 0;
			virtual void Pause() = 0;

			virtual void SetPosition(int milisenconds) = 0;
			virtual int GetPosition() = 0;

			virtual bool HaveAudio() = 0;

			friend class VideoManager;
		};
	}
}

#endif
