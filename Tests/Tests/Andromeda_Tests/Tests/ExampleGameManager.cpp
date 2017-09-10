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
	exampleState = TestHelper::Instance()->GetCurrentTest();
	exampleState->Init();

	ChangeState(exampleState);
}

void ExampleGameManager::CleanUp()
{
	//Andromeda::Utils::Logger_Info("GameManager - Clean up\n");
	//exampleState->CleanUp();

	//Andromeda::Utils::Logger_Info("GameManager - Delete state\n");
	delete exampleState;

	//tests
	//Andromeda::Utils::Logger_Info("Sprites count: %d\n", Andromeda::Graphics::Sprite::GetObjectCount());
	//Andromeda::Utils::Logger_Info("VertexArray count: %d\n", Andromeda::Graphics::VertexArrayObject::GetObjectCount());
}