#ifndef GameLoaderGxm_H
#define GameLoaderGxm_H

#include <Andromeda/System/GameLoader.h>
#include <Andromeda/Graphics/RenderManager.h>

namespace Andromeda
{
	namespace System
	{
		class GameLoaderGxm : public GameLoader
		{
		private:

			Graphics::RenderManager* _renderManager;

		public:

			GameLoaderGxm(GameManager* gameManager);

			void Run();
		};
	}
}

#endif