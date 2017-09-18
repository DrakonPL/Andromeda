#include "Test4.h"
#include <Andromeda/Graphics/GraphicsEnums.h>

#include "../TestHelper.h"
#include "../InputHelper.h"


void Test4::Init()
{
	_renderManager = RenderManager::Instance();
	_shaderManager = ShaderManager::Instance();
	_textureManager = TextureManager::Instance();
	
	//load shader
	_shader = _shaderManager->LoadFromFile("simple", "Assets/Shaders/vertex_color_texture", "Assets/Shaders/vertex_color_texture", TextureColor);
	
	//load texture
	_texture = _textureManager->LoadFromFile("Assets/Images/wall.png");

	//create data buffer object
	_arrayObject = _renderManager->CreateVertexArrayObject(TextureColor, StaticDraw);

	//create vertices
	_arrayObject->CreateVertices(3);

	//get vertices
	TextureColorVertex* _simpleData = static_cast<TextureColorVertex*>(_arrayObject->GetVertices());

	_simpleData[0].x = 0.5f;	_simpleData[0].y = -0.5f;	_simpleData[0].z = 0.0f;
	_simpleData[1].x = -0.5f;	_simpleData[1].y = -0.5f;	_simpleData[1].z = 0.0f;
	_simpleData[2].x = 0.0f;	_simpleData[2].y = 0.5f;	_simpleData[2].z = 0.0f;

	_simpleData[0].r = 1.0f;	_simpleData[0].g = 0.0f;	_simpleData[0].b = 0.0f;
	_simpleData[1].r = 0.0f;	_simpleData[1].g = 1.0f;	_simpleData[1].b = 0.0f;
	_simpleData[2].r = 0.0f;	_simpleData[2].g = 0.0f;	_simpleData[2].b = 1.0f;

	_simpleData[0].u = 1.0f;	_simpleData[0].v = 0.0f;	
	_simpleData[1].u = 0.0f;	_simpleData[1].v = 0.0f;	
	_simpleData[2].u = 0.5f;	_simpleData[2].v = 1.0f;		

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

void Test4::Enter()
{

}

void Test4::CleanUp()
{
	delete _arrayObject;

	_shaderManager->Remove(_shader);
	_textureManager->Remove(_texture);
}

void Test4::Pause()
{

}

void Test4::Resume()
{

}

void Test4::GamePause()
{

}

void Test4::GameResume()
{

}

void Test4::HandleEvents(GameManager* manager)
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

void Test4::Update(GameManager* manager)
{

}

void Test4::Draw(GameManager* manager)
{
	//start frame
	_renderManager->StartFrame();

	//clear screen
	_renderManager->ClearScreen();

	//use texture
	_renderManager->UseTexture(_texture);

	//use shader
	_shader->Bind();

	//draw vertices
	_arrayObject->Draw();

	//draw test info
	TestHelper::Instance()->ShowInfoText();

	//end frame
	_renderManager->EndFrame();
}