#include "Test2.h"
#include <Andromeda/Graphics/GraphicsEnums.h>
#include <stdlib.h>

#include "../TestHelper.h"
#include "../InputHelper.h"


void Test2::Init()
{
	_renderManager = RenderManager::Instance();
	_shaderManager = ShaderManager::Instance();

	//load shader
	_shader = _shaderManager->LoadFromFile("simple", "Assets/Shaders/simple_triangle", "Assets/Shaders/simple_color_uniform", Simple);
	
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

void Test2::Enter()
{

}

void Test2::CleanUp()
{
	_shaderManager->RemoveAll();
	delete _arrayObject;
}

void Test2::Pause()
{

}

void Test2::Resume()
{

}

void Test2::GamePause()
{

}

void Test2::GameResume()
{

}

void Test2::HandleEvents(GameManager* manager)
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

void Test2::Update(GameManager* manager)
{

}

void Test2::Draw(GameManager* manager)
{
	//start frame
	_renderManager->StartFrame();

	//clear screen
	_renderManager->ClearScreen();

	//use shader
	_shader->Bind();

	//change color uniform in shader
	glm::vec4 myColor(0.5f, 0.0f, 0.0f, 1.0f);
	_shader->SetUniform(FragmentShader, "myColor", myColor);

	//draw vertices
	_arrayObject->Draw();

	//end frame
	_renderManager->EndFrame();
}