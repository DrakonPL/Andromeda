#include "Test3.h"
#include <Andromeda/Graphics/GraphicsEnums.h>

#include "../TestHelper.h"
#include "../InputHelper.h"


void Test3::Init()
{
	_renderManager = RenderManager::Instance();
	_shaderManager = ShaderManager::Instance();

	//load shader
	_shader = _shaderManager->LoadFromFile("simple", "Assets/Shaders/vertex_color", "Assets/Shaders/vertex_color", Color);

	//create data buffer object
	_arrayObject = _renderManager->CreateVertexArrayObject(Color, StaticDraw);

	//create vertices
	_arrayObject->CreateVertices(3);

	//get vertices
	ColorVertex* _simpleData = static_cast<ColorVertex*>(_arrayObject->GetVertices());

	_simpleData[0].x = 0.5f;	_simpleData[0].y = -0.5f;	_simpleData[0].z = 0.0f;
	_simpleData[1].x = -0.5f;	_simpleData[1].y = -0.5f;	_simpleData[1].z = 0.0f;
	_simpleData[2].x = 0.0f;	_simpleData[2].y = 0.5f;	_simpleData[2].z = 0.0f;

	_simpleData[0].r = 1.0f;	_simpleData[0].g = 0.0f;	_simpleData[0].b = 0.0f;
	_simpleData[1].r = 0.0f;	_simpleData[1].g = 1.0f;	_simpleData[1].b = 0.0f;
	_simpleData[2].r = 0.0f;	_simpleData[2].g = 0.0f;	_simpleData[2].b = 1.0f;

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

void Test3::Enter()
{

}

void Test3::CleanUp()
{
	_shaderManager->RemoveAll();
	delete _arrayObject;
}

void Test3::Pause()
{

}

void Test3::Resume()
{

}

void Test3::GamePause()
{

}

void Test3::GameResume()
{

}

void Test3::HandleEvents(GameManager* manager)
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

void Test3::Update(GameManager* manager)
{

}

void Test3::Draw(GameManager* manager)
{
	//start frame
	_renderManager->StartFrame();

	//clear screen
	_renderManager->ClearScreen();

	//use shader
	_shader->Bind();

	//draw vertices
	_arrayObject->Draw();

	//end frame
	_renderManager->EndFrame();
}