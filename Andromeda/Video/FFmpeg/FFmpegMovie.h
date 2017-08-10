#ifndef FFmpegMovie_H
#define FFmpegMovie_H

#include <Andromeda/Video/Movie.h>
#include <Andromeda/Video/FFmpeg/AvVideoPlayer.h>
#include <string>

namespace Andromeda
{
	namespace Video
	{
		class FFmpegVideoManager;

		class FFmpegMovie : Movie
		{
		private:

			AvVideoPlayer* _videoPlayer;

			FFmpegMovie(std::string name);
			FFmpegMovie(std::string name, glm::vec2 position, glm::vec2 size);

		public:

			~FFmpegMovie();

			bool IsPlaying();
			bool Load(std::string filePath);

			void Update(float dt);

			void Play();
			void Stop();
			void Pause();

			void SetPosition(int milisenconds);
			int GetPosition();

			bool HaveAudio();

			void AudioOut(float *output, int bufferSize, int nChannels);

			friend class FFmpegVideoManager;
		};
	}
}

#endif
