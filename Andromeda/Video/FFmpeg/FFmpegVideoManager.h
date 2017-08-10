#ifndef FFmpegVideoManager_H
#define FFmpegVideoManager_H

#include <Andromeda/Video/VideoManager.h>
#include <Andromeda/Video/Movie.h>

//std
#include <string>

//port
#include "portaudio.h"

namespace Andromeda
{
	namespace Video
	{
		class FFmpegVideoManager : public VideoManager
		{
		private:

			PaStream* _paStream;

			bool InitAudio();

			static int AudioCallback(const void *input, void *output,
				unsigned long frameCount,
				const PaStreamCallbackTimeInfo* timeInfo,
				PaStreamCallbackFlags statusFlags,
				void* userData);

		public:

			FFmpegVideoManager();
			~FFmpegVideoManager();

			bool Init();

			Movie* GetMovie(std::string name);
			Movie* GetMovie(std::string name, glm::vec2 position, glm::vec2 size);

			void Update(float dt);
		};
	}
}

#endif