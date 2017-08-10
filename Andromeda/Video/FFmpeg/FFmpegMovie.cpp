#include <Andromeda/Video/FFmpeg/FFmpegMovie.h>

namespace Andromeda
{
	namespace Video
	{
		FFmpegMovie::FFmpegMovie(std::string name) : Movie(name)
		{
			_videoPlayer = new AvVideoPlayer();
			_videoPlayer->setupAudioOut(2, 44100);
		}

		FFmpegMovie::FFmpegMovie(std::string name, glm::vec2 position, glm::vec2 size) : Movie(name,position,size)
		{
			_videoPlayer = new AvVideoPlayer();
			_videoPlayer->setupAudioOut(2, 44100);
		}

		FFmpegMovie::~FFmpegMovie()
		{
			delete _videoPlayer;
		}

		bool FFmpegMovie::IsPlaying()
		{
			return _videoPlayer->getIsPlaying();
		}

		bool FFmpegMovie::Load(std::string filePath)
		{
			bool loaded = _videoPlayer->load(filePath);
			if (loaded)
			{
				_texture = _videoPlayer->getTexture();
			}
			return loaded;
		}

		void FFmpegMovie::Update(float dt)
		{
			_videoPlayer->update(dt);
		}

		bool FFmpegMovie::HaveAudio()
		{
			return _videoPlayer->getIsAudio();
		}

		void FFmpegMovie::Play()
		{
			_videoPlayer->play();
		}

		void FFmpegMovie::Stop()
		{
			_videoPlayer->stop();
		}

		void FFmpegMovie::Pause()
		{
			
		}

		void FFmpegMovie::SetPosition(int milisenconds)
		{
			_videoPlayer->setPositionMS(milisenconds);
		}

		int FFmpegMovie::GetPosition()
		{
			return _videoPlayer->getDurationMs();
		}

		void FFmpegMovie::AudioOut(float *output, int bufferSize, int nChannels)
		{
			_videoPlayer->audioOut(output, bufferSize, nChannels);
		}
	}
}
