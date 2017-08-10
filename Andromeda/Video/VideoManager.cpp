#include <Andromeda/Video/VideoManager.h>

#ifdef ANDROMEDA_PC
#include <Andromeda/Video/FFmpeg/FFmpegVideoManager.h>
#endif

#ifdef ANDROMEDA_VITA
//#include <Andromeda/Video/Vita/VitaVideoManager.h>
#endif


namespace Andromeda
{
	namespace Video
	{
		VideoManager* VideoManager::_videoManager = 0;

		VideoManager::VideoManager()
		{

		}

		VideoManager::~VideoManager()
		{

		}

		VideoManager* VideoManager::Instance()
		{
			if (_videoManager == 0)
			{
#ifdef ANDROMEDA_PC
				{
					_videoManager = new FFmpegVideoManager();
				}
#endif

#ifdef ANDROMEDA_VITA
				{
					//_videoManager = new VitaVideoManager();
				}
#endif

				_videoManager->Init();
			}

			return _videoManager;
		}
	}
}