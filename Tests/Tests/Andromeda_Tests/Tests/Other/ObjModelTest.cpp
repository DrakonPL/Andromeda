#include "ObjModelTest.h"
#include <Andromeda/Graphics/GraphicsEnums.h>
#include <stdlib.h>

#include "../TestHelper.h"
#include "../InputHelper.h"

#include "Andromeda/Graphics/Models/ModelObj.h"


void ObjModelTest::Init()
{
	_renderManager = RenderManager::Instance();
	_shaderManager = ShaderManager::Instance();
	_textureManager = TextureManager::Instance();

	_counter = 0;
	_maxTests = 500;
}

void ObjModelTest::Enter()
{

}

void ObjModelTest::CleanUp()
{

}

void ObjModelTest::Pause()
{

}

void ObjModelTest::Resume()
{

}

void ObjModelTest::GamePause()
{

}

void ObjModelTest::GameResume()
{

}

void ObjModelTest::HandleEvents(GameManager* manager)
{
	if (InputHelper::Instance()->ActionPressed(InputAction::Next))
	{
		TestHelper::Instance()->NextTest(manager);
	}

	if (InputHelper::Instance()->ActionPressed(InputAction::Exit))
	{
		manager->Quit();
	}

	InputHelper::Instance()->Update();
}

void ObjModelTest::Update(GameManager* manager)
{
	if (_counter < _maxTests)
	{
		ModelObj*_model = new ModelObj();
		_model->LoadBinary("Assets/Models/Obj/Imrod/imrod.objb");
		delete _model;

		_counter++;
	}
}

void ObjModelTest::Draw(GameManager* manager)
{
	//start frame
	_renderManager->StartFrame();

	//clear screen
	_renderManager->ClearScreen();

	//draw test info
	std::string text = std::string("Test ModelObj : ") + std::to_string(_counter);

	TestHelper::Instance()->AddInfoText(text);
	TestHelper::Instance()->ShowInfoText();

	//end frame
	_renderManager->EndFrame();
}