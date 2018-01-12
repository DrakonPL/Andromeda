#include "ShaderTest.h"
#include <Andromeda/Graphics/GraphicsEnums.h>
#include <stdlib.h>

#include "../TestHelper.h"
#include "../InputHelper.h"


void ShaderTest::Init()
{
	_renderManager = RenderManager::Instance();
	_shaderManager = ShaderManager::Instance();
	_textureManager = TextureManager::Instance();

	_counter = 0;
	_maxTests = 500;
}

void ShaderTest::Enter()
{

}

void ShaderTest::CleanUp()
{

}

void ShaderTest::Pause()
{

}

void ShaderTest::Resume()
{

}

void ShaderTest::GamePause()
{

}

void ShaderTest::GameResume()
{

}

void ShaderTest::HandleEvents(GameManager* manager)
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

void ShaderTest::Update(GameManager* manager)
{
	if (_counter < _maxTests)
	{
		Shader* shader = _shaderManager->LoadFromFile("simple", "Assets/Shaders/vertex_color_texture_transform_3d", "Assets/Shaders/vertex_color_texture", TextureColor);

		shader->Bind();		

		_shaderManager->Remove(shader);

		_counter++;
	}
}

void ShaderTest::Draw(GameManager* manager)
{
	//start frame
	_renderManager->StartFrame();

	//clear screen
	_renderManager->ClearScreen();

	//draw test info
	std::string text = std::string("Test shader: ") + std::to_string(_counter);

	TestHelper::Instance()->AddInfoText(text);
	TestHelper::Instance()->ShowInfoText();

	//end frame
	_renderManager->EndFrame();
}