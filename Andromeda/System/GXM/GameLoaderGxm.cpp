#include <Andromeda/System/GXM/GameLoaderGxm.h>
#include <Andromeda/FileSystem/FileManager.h>
#include <Andromeda/Input/InputManager.h>
#include <Andromeda/Utils/Logger.h>

#include <psp2/ctrl.h>
#include <psp2/touch.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/sysmodule.h>
#include <psp2/io/dirent.h>
#include <psp2/io/fcntl.h>

namespace Andromeda
{
	namespace System
	{
		GameLoaderGxm::GameLoaderGxm(GameManager* gameManager) : GameLoader(gameManager)
		{
			
		}

		void GameLoaderGxm::Run()
		{
			//hack
			sceIoMkdir("ux0:/data/tests", 0777);
			
			//set main dir location
			FileSystem::FileManager::Instance()->SetMainDirPath("app0:/");
			FileSystem::FileManager::Instance()->SetSaveDirPath("ux0:/data/tests/");

			//
			Utils::Logger::Instance()->Log("Start\n");

			//set configuration 
			Utils::Logger::Instance()->Log("Config\n");
			_gameManager->Configure();

			//create renderer
			Utils::Logger::Instance()->Log("Render manager\n");
			_renderManager = Graphics::RenderManager::Instance();
			_renderManager->Init();

			//touch controls
			Utils::Logger::Instance()->Log("Controls\n");
			sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG_WIDE);
			sceTouchSetSamplingState(SCE_TOUCH_PORT_FRONT, 1);
			sceTouchSetSamplingState(SCE_TOUCH_PORT_BACK, 1);



			//set input manager
			Utils::Logger::Instance()->Log("Input manager\n");
			Input::InputManager* intputManager = Input::InputManager::Instance();

			//init game manager 
			Utils::Logger::Instance()->Log("Init game manager\n");
			_gameManager->Init();

			//main loop
			Utils::Logger::Instance()->Log("Run\n");
			while (_gameManager->Running())
			{
				//system events
				sceKernelPowerTick(SCE_KERNEL_POWER_TICK_DISABLE_AUTO_SUSPEND);
				sceKernelPowerTick(SCE_KERNEL_POWER_TICK_DISABLE_OLED_OFF);

				//update input manager
				intputManager->Update();

				//game stuff
				_gameManager->HandleEvents();
				_gameManager->Update();
				_gameManager->Draw();

				//end frame
				_renderManager->SwapBuffers();
			}

			//clean exit
			Utils::Logger::Instance()->Log("Clean up\n");
			_gameManager->CleanUp();

			//exit
			Utils::Logger::Instance()->Log("Finish render manager\n");
			_renderManager->Finish();

			//remove render manager
			delete _renderManager;
			
			//log exit
			Utils::Logger::Instance()->Log("Exit\n");
			sceKernelExitProcess(0);
		}
	}
}
