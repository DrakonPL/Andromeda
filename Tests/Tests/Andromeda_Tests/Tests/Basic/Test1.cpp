#include "Test1.h"
#include <Andromeda/Graphics/GraphicsEnums.h>
#include <stdlib.h>

#include "../TestHelper.h"
#include "../InputHelper.h"


void Test1::Init()
{
	_renderManager = RenderManager::Instance();
	_shaderManager = ShaderManager::Instance();

	//load shader
	_shader = _shaderManager->LoadFromFile("simple", "Assets/Shaders/simple_triangle", "Assets/Shaders/simple_triangle", Simple);

	//create data buffer object
	_arrayObject = _renderManager->CreateVertexArrayObject(Simple, StaticDraw);

	//create vertices
	_arrayObject->CreateVertices(3);

	//get vertices
	SimpleVertex* _simpleData = static_cast<SimpleVertex*>(_arrayObject->GetVertices());

	//set data
	_simpleData[0].x = -0.5f;	_simpleData[0].y = -0.5f;	_simpleData[0].z = 0.0f;
	_simpleData[1].x = 0.5f;	_simpleData[1].y = -0.5f;	_simpleData[1].z = 0.0f;
	_simpleData[2].x = 0.0f;	_simpleData[2].y = 0.5f;	_simpleData[2].z = 0.0f;

	//create indices
	_arrayObject->CreateIndices(3);

	//get indices
	unsigned short* _indices = static_cast<unsigned short*>(_arrayObject->GetIndices());

	//set data
	_indices[0] = 0;
	_indices[1] = 1;
	_indices[2] = 2;

	//generate buffer object
	_arrayObject->Generate();
}

void Test1::Enter()
{

}

void Test1::CleanUp()
{
	delete _arrayObject;

	_shaderManager->Remove(_shader);
}

void Test1::Pause()
{

}

void Test1::Resume()
{

}

void Test1::GamePause()
{

}

void Test1::GameResume()
{

}

void Test1::HandleEvents(GameManager* manager)
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

void Test1::Update(GameManager* manager)
{

}

void Test1::Draw(GameManager* manager)
{
	//start frame
	_renderManager->StartFrame();

	//clear screen
	_renderManager->ClearScreen();

	//use shader
	_shader->Bind();

	//draw vertices
	_arrayObject->Draw();

	//draw test info
	TestHelper::Instance()->AddInfoText("Simple triangle - color in shader.");
	TestHelper::Instance()->ShowInfoText();

	//end frame
	_renderManager->EndFrame();
}