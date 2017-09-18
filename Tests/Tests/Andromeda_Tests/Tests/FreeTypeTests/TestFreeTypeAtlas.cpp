#include "TestFreeTypeAtlas.h"

#include "../TestHelper.h"
#include "../InputHelper.h"

void TestFreeTypeAtlas::Init()
{
	_renderManager = RenderManager::Instance();
	_shaderManager = ShaderManager::Instance();
	_textureManager = TextureManager::Instance();

	//atlas
	_atlas = new TextureAtlas(512, 512);

	//font
	size_t minsize = 8, maxsize = 30;
	size_t count = maxsize - minsize;
	size_t i, missed = 0;

	for (i = minsize; i < maxsize; ++i)
	{
		_font = new TexturedFont(_atlas, i, "Assets/Fonts/Vera.ttf");

		//load some text
		const char * cache = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
		_font->CacheGlyphs(cache);

		delete _font;
	}
	
	//upload texture
	_texture = _atlas->CreateTexture();

	//load shader
	_shader = _shaderManager->LoadFromFile("sprite", "Assets/Shaders/sprite", "Assets/Shaders/sprite", Textured);

	//sprites
	_sprite = new Sprite("atlas", _texture, _shader);
	_sprite->SetPosition(glm::vec2(_renderManager->GetWidth() / 2, _renderManager->GetHeight() / 2));


	_projection = glm::ortho(0.0f, (float)_renderManager->GetWidth(), (float)_renderManager->GetHeight(), 0.0f, -1.0f, 1.0f);

	_renderManager->SetDepth(false);
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
	TestHelper::Instance()->ShowInfoText();

	//end frame
	_renderManager->EndFrame();
}