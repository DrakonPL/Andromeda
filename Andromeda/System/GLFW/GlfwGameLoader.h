#ifndef GlfwGameLoader_H
#define GlfwGameLoader_H

#include <Andromeda/System/GameLoader.h>
#include <Andromeda/Graphics/RenderManager.h>

// GLFW
#include <GLFW/glfw3.h>


namespace Andromeda
{
	namespace System
	{
		class GlfwGameLoader : public GameLoader
		{
		private:

			GLFWwindow* _window;
			Graphics::RenderManager* _renderManager;

		public:

			GlfwGameLoader(GameManager* gameManager);

			void Run();
		};
	}
}

#endif GlfwGameLoader_H