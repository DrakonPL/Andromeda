#include "TestFreeTypeFont.h"

#include "../TestHelper.h"
#include "../InputHelper.h"

void TestFreeTypeFont::Init()
{
	_renderManager = RenderManager::Instance();
	_shaderManager = ShaderManager::Instance();
	_textureManager = TextureManager::Instance();

	//chars to cache
	const char * cache = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

	_fontShader = _shaderManager->LoadFromFile("font", "Assets/Shaders/font", "Assets/Shaders/font", TextureColor);

	//common
	_fontatlas = new TextureAtlas(512, 512);

	_font = new TexturedFont(_fontatlas, 16, "Assets/Fonts/MODES.TTF");
	_font->CacheGlyphs(cache);
	_font->SetShader(_fontShader);

	_fontatlas->CreateTexture();

	//atlas
	_atlas = new TextureAtlas(512, 512);

	//font
	_font1 = new TexturedFont(_atlas, 16, "Assets/Fonts/SourceCodePro-Regular.ttf");
	_font1->CacheGlyphs(cache);
	_font1->SetShader(_fontShader);

	_font2 = new TexturedFont(_atlas, 32, "Assets/Fonts/JellyFont.ttf");
	_font2->CacheGlyphs(cache);
	_font2->SetShader(_fontShader);

	_font3 = new TexturedFont(_atlas, 64, "Assets/Fonts/Lobster-Regular.ttf");
	_font3->CacheGlyphs(cache);
	_font3->SetShader(_fontShader);

	//upload texture
	_atlas->CreateTexture();

	_projection = glm::ortho(0.0f, (float)_renderManager->GetWidth(), (float)_renderManager->GetHeight(), 0.0f, -1.0f, 1.0f);

	_renderManager->SetDepth(false);

	//input

}

void TestFreeTypeFont::Enter()
{
	InputHelper::Instance()->Update();
}

void TestFreeTypeFont::CleanUp()
{
	delete _font;

	delete _font1;
	delete _font2;
	delete _font3;

	delete _atlas;
	delete _fontatlas;

	_textureManager->RemoveAll();
	_shaderManager->RemoveAll();
}

void TestFreeTypeFont::Pause()
{

}

void TestFreeTypeFont::Resume()
{

}

void TestFreeTypeFont::GamePause()
{

}

void TestFreeTypeFont::GameResume()
{

}

void TestFreeTypeFont::HandleEvents(GameManager* manager)
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

void TestFreeTypeFont::Update(GameManager* manager)
{

}

void TestFreeTypeFont::Draw(GameManager* manager)
{
	//start frame
	_renderManager->StartFrame();

	//clear screen
	_renderManager->ClearScreen();

	_font1->AddText("Font rendering is working!!!", _renderManager->GetWidth() / 2, _renderManager->GetHeight() / 5, glm::vec3(1.0f, 0.0f, 1.0f), FontCenter);
	_font1->Draw(_projection);

	_font2->AddText("Font rendering is working!!!", _renderManager->GetWidth() / 2, _renderManager->GetHeight() / 3, glm::vec3(1.0f, 1.0f, 0.0f), FontCenter);
	_font2->Draw(_projection);

	_font3->AddText("Font rendering is working!!!", _renderManager->GetWidth() / 2, _renderManager->GetHeight() / 2, glm::vec3(1.0f, 1.0f, 1.0f), FontCenter);
	_font3->Draw(_projection);


	_font->AddText("Press X to change test", _renderManager->GetWidth() / 2, _renderManager->GetHeight() - 2, glm::vec3(1.0f, 1.0f, 1.0f), FontCenter);
	_font->Draw(_projection);

	//end frame
	_renderManager->EndFrame();
}