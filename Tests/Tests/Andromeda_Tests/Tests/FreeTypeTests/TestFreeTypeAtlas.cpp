#include "TestFreeTypeAtlas.h"

#include "../TestHelper.h"
#include "../InputHelper.h"

#include <Andromeda/Utils/Logger.h>

void TestFreeTypeAtlas::Init()
{
	_renderManager = RenderManager::Instance();
	_shaderManager = ShaderManager::Instance();
	_textureManager = TextureManager::Instance();

	Andromeda::Utils::Logger::Instance()->Log("Create Atlas \n");

	//atlas
	_atlas = new TextureAtlas(512, 512);

	//font
	size_t minsize = 8, maxsize = 30;
	size_t count = maxsize - minsize;
	size_t i, missed = 0;



	for (i = minsize; i < maxsize; ++i)
	{
		Andromeda::Utils::Logger::Instance()->Log("Create font size: %d \n",i);

		_font = new TexturedFont(_atlas, i, "Assets/Fonts/Vera.ttf");

		Andromeda::Utils::Logger::Instance()->Log("cache glymphs \n");

		//load some text
		const char * cache = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
		_font->CacheGlyphs(cache);

		Andromeda::Utils::Logger::Instance()->Log("delete font \n");

		delete _font;
	}

	Andromeda::Utils::Logger::Instance()->Log("create texture\n");
	
	//upload texture
	_texture = _atlas->CreateTexture();

	//load shader

	Andromeda::Utils::Logger::Instance()->Log("load shader\n");
	_shader = _shaderManager->LoadFromFile("sprite", "Assets/Shaders/sprite", "Assets/Shaders/sprite", Textured);

	//sprites
	Andromeda::Utils::Logger::Instance()->Log("create sprite\n");
	_sprite = new Sprite("atlas", _texture, _shader);
	_sprite->SetPosition(glm::vec2(_renderManager->GetWidth() / 2, _renderManager->GetHeight() / 2));


	_projection = glm::ortho(0.0f, (float)_renderManager->GetWidth(), (float)_renderManager->GetHeight(), 0.0f, -1.0f, 1.0f);

	_renderManager->SetDepth(false);

	Andromeda::Utils::Logger::Instance()->Log("start\n");
}

void TestFreeTypeAtlas::Enter()
{
	InputHelper::Instance()->Update();
}

void TestFreeTypeAtlas::CleanUp()
{
	delete _atlas;
	delete _sprite;

	_shaderManager->Remove(_shader);
}

void TestFreeTypeAtlas::Pause()
{

}

void TestFreeTypeAtlas::Resume()
{

}

void TestFreeTypeAtlas::GamePause()
{

}

void TestFreeTypeAtlas::GameResume()
{

}

void TestFreeTypeAtlas::HandleEvents(GameManager* manager)
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

void TestFreeTypeAtlas::Update(GameManager* manager)
{

}

void TestFreeTypeAtlas::Draw(GameManager* manager)
{
	//start frame
	_renderManager->StartFrame();

	//clear screen
	_renderManager->ClearScreen();

	//test
	_sprite->SetSolor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	_sprite->Draw(_projection);

	//draw test info
	TestHelper::Instance()->AddInfoText("Atlas texture test.");
	TestHelper::Instance()->ShowInfoText();

	//end frame
	_renderManager->EndFrame();
}