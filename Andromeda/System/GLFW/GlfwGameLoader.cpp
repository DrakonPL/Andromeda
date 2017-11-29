#include <Andromeda/System/GLFW/GlfwGameLoader.h>
#include <Andromeda/Input/InputManager.h>
#include <Andromeda/Input/GLFW/InputManagerGlfw.h>
#include <Andromeda/Utils/Logger.h>

#include <iostream>

namespace Andromeda
{
	namespace System
	{
		GlfwGameLoader::GlfwGameLoader(GameManager* gameManager) : GameLoader(gameManager)
		{
			_window = 0;
			_renderManager = 0;
		}

		void GlfwGameLoader::Run()
		{
			Utils::Logger_Info("Start\n");
			Utils::Logger::Logger_Info("Start\n");

			//init library
			if (!glfwInit())
			{
				Utils::Logger_Info("Failed to create initialize GLFW\n");
				return;
			}

			//set configuration 
			_gameManager->Configure();

			//opengl version
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

			//get render manager
			_renderManager = Graphics::RenderManager::Instance();

			//get default monitor
			GLFWmonitor* monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* mode = glfwGetVideoMode(monitor);

			if (_renderManager->GetWidth() == -1 || _renderManager->GetHeight() == -1)
			{
				_renderManager->SetWindowSize(mode->width, mode->height);
			}

			//create window
			if (_renderManager->IsFullScreen())
			{
				_window = glfwCreateWindow(_renderManager->GetWidth(), _renderManager->GetHeight(), "Vita Simulator", monitor, nullptr);
			}
			else
			{
				_window = glfwCreateWindow(_renderManager->GetWidth(), _renderManager->GetHeight(), "Vita Simulator", nullptr, nullptr);
			}

			//check if window was screated
			if (_window == 0)
			{
				std::cout << "Failed to create GLFW window" << std::endl;
				glfwTerminate();
				return;
			}

			//create rendering context
			glfwMakeContextCurrent(_window);
			glfwSwapInterval(1);

			//set input manager
			Input::InputManager* intputManager = Input::InputManager::Instance();
			static_cast<Input::InputManagerGlfw*>(intputManager)->SetGlfwWindow(_window);			

			//create renderer			
			_renderManager->Init();

			//init game manager 
			_gameManager->Init();

			//main loop
			while (_gameManager->Running() && !glfwWindowShouldClose(_window))
			{
				//system events
				glfwPollEvents();

				//update input manager
				intputManager->Update();

				//game stuff
				_gameManager->HandleEvents();
				_gameManager->Update();
				_gameManager->Draw();

				//end frame
				glfwSwapBuffers(_window);
			}

			//clean game manager
			_gameManager->CleanUp();

			//finish render manager;
			_renderManager->Finish();

			//log exit
			Utils::Logger_Info("Exit\n");

			//exit
			glfwTerminate();
		}

	}
}