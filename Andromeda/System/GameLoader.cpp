#include <Andromeda/System/GameLoader.h>

#ifdef ANDROMEDA_GLFW
#include <Andromeda/System/GLFW/GlfwGameLoader.h>
#endif

#ifdef ANDROMEDA_VITA
#include <Andromeda/System/GXM/GameLoaderGxm.h>
#endif

namespace Andromeda
{
	namespace System
	{
		GameLoader::GameLoader(GameManager* gameManager)
		{
			_gameManager = gameManager;
		}

		GameLoader* GameLoader::Create(GameManager* gameManager)
		{
			GameLoader* _loader = 0;

			#ifdef ANDROMEDA_GLFW
			{
				_loader = new GlfwGameLoader(gameManager);
			}
			#endif

			#ifdef ANDROMEDA_VITA
			{
				_loader = new GameLoaderGxm(gameManager);
			}
			#endif
			
			return _loader;
		}
	}
}
