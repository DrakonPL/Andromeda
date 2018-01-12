#include "FontTest.h"
#include <Andromeda/Graphics/GraphicsEnums.h>
#include <stdlib.h>

#include "../TestHelper.h"
#include "../InputHelper.h"

#include "Andromeda/Graphics/Models/ModelObj.h"


void FontTest::Init()
{
	_renderManager = RenderManager::Instance();
	_shaderManager = ShaderManager::Instance();
	_textureManager = TextureManager::Instance();

	_counter = 0;
	_maxTests = 500;
}

void FontTest::Enter()
{

}

void FontTest::CleanUp()
{

}

void FontTest::Pause()
{

}

void FontTest::Resume()
{

}

void FontTest::GamePause()
{

}

void FontTest::GameResume()
{

}

void FontTest::HandleEvents(GameManager* manager)
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

void FontTest::Update(GameManager* manager)
{
	if (_counter < _maxTests)
	{
		const char * cache = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

		TextureAtlas* fontatlas = new TextureAtlas(512, 512);

		TexturedFont* font = new TexturedFont(fontatlas, 16, "Assets/Fonts/MODES.TTF");
		font->CacheGlyphs(cache);

		fontatlas->CreateTexture();

		//
		delete font;
		delete fontatlas;

		_counter++;
	}
}

void FontTest::Draw(GameManager* manager)
{
	//start frame
	_renderManager->StartFrame();

	//clear screen
	_renderManager->ClearScreen();

	//draw test info
	std::string text = std::string("Test Font : ") + std::to_string(_counter);

	TestHelper::Instance()->AddInfoText(text);
	TestHelper::Instance()->ShowInfoText();

	//end frame
	_renderManager->EndFrame();
}