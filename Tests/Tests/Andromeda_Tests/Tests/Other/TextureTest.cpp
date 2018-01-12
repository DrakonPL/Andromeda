#include "TextureTest.h"
#include <Andromeda/Graphics/GraphicsEnums.h>
#include <stdlib.h>

#include "../TestHelper.h"
#include "../InputHelper.h"


void TextureTest::Init()
{
	_renderManager = RenderManager::Instance();
	_shaderManager = ShaderManager::Instance();
	_textureManager = TextureManager::Instance();

	_counter = 0;
	_maxTests = 500;
}

void TextureTest::Enter()
{

}

void TextureTest::CleanUp()
{

}

void TextureTest::Pause()
{

}

void TextureTest::Resume()
{

}

void TextureTest::GamePause()
{

}

void TextureTest::GameResume()
{

}

void TextureTest::HandleEvents(GameManager* manager)
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

void TextureTest::Update(GameManager* manager)
{
	if (_counter < _maxTests)
	{
		Texture* texture = _textureManager->LoadFromFile("Assets/Images/bird_sheet.png", TextureFilerType::NearestFilter);
		_textureManager->Remove(texture);

		_counter++;
	}
}

void TextureTest::Draw(GameManager* manager)
{
	//start frame
	_renderManager->StartFrame();

	//clear screen
	_renderManager->ClearScreen();

	//draw test info
	std::string text = std::string("Test texture: ") + std::to_string(_counter);

	TestHelper::Instance()->AddInfoText(text);
	TestHelper::Instance()->ShowInfoText();

	//end frame
	_renderManager->EndFrame();
}