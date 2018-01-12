#include <Andromeda/Graphics/RenderManager.h>
#include "Andromeda/Graphics/Sprite.h"
#include <Andromeda/Utils/Logger.h>

#include "ExampleGameManager.h"
#include "TestHelper.h"


void ExampleGameManager::Configure()
{
	//set pc resolution
	#ifdef ANDROMEDA_GL3
	{
		Andromeda::Graphics::RenderManager::Instance()->SetWindowSize(960, 544);

		//Andromeda::Graphics::RenderManager::Instance()->SetWindowSize(-1, -1);
		//Andromeda::Graphics::RenderManager::Instance()->SetFullScreen(true);
	}
	#endif	
}


void ExampleGameManager::Init()
{
	//init whatever you need
	ChangeState(TestHelper::Instance()->GetCurrentTest());
}

void ExampleGameManager::CleanUp()
{
	delete TestHelper::Instance();
}