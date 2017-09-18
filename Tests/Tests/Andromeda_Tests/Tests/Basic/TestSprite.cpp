#include "TestSprite.h"

#include "../TestHelper.h"
#include "../InputHelper.h"

void TestSprite::Init()
{
	_renderManager = RenderManager::Instance();
	_shaderManager = ShaderManager::Instance();
	_textureManager = TextureManager::Instance();

	//load shader
	_shader = _shaderManager->LoadFromFile("simple", "Assets/Shaders/sprite", "Assets/Shaders/sprite", Textured);

	//load texture
	_texture = _textureManager->LoadFromFile("Assets/Images/bird_sheet.png", TextureFilerType::NearestFilter);
	_warningTexture = _textureManager->LoadFromFile("Assets/Images/warning.png");
	_boxTexture = _textureManager->LoadFromFile("Assets/Images/container.png");

	//sprites
	_warning = new Sprite("warning", "Assets/Images/warning.png", "Assets/Shaders/sprite", "Assets/Shaders/sprite");
	_warning->SetPosition(glm::vec2(_renderManager->GetWidth() / 2, _renderManager->GetHeight() / 2));

	//title
	_title = new Sprite("title", _texture,_shader,glm::vec2(145.0f, 172.0f), glm::vec2(97.0f,23.0f));
	_title->SetPosition(glm::vec2(_renderManager->GetWidth() / 2, 60.0f));
	_title->SetScale(glm::vec2(2.125f, 2.125f));

	//background
	_background = new Sprite("background", _texture, _shader, glm::vec2(0.0f, 0.0f), glm::vec2(144.0f, 256.0f));
	_background->SetPosition(glm::vec2(_renderManager->GetWidth() / 2, _renderManager->GetHeight() / 2));
	_background->SetScale(glm::vec2(2.125f, 2.125f));

	_projection = glm::ortho(0.0f, (float)_renderManager->GetWidth(), (float)_renderManager->GetHeight(), 0.0f, -1.0f, 1.0f);

	_renderManager->SetDepth(false);
}

void TestSprite::Enter()
{

}

void TestSprite::CleanUp()
{
	delete _warning;
	delete _title;
	delete _background;

	_textureManager->Remove(_texture);
	_textureManager->Remove(_warningTexture);
	_textureManager->Remove(_boxTexture);

	_shaderManager->Remove(_shader);
}

void TestSprite::Pause()
{

}

void TestSprite::Resume()
{

}

void TestSprite::GamePause()
{

}

void TestSprite::GameResume()
{

}

void TestSprite::HandleEvents(GameManager* manager)
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

void TestSprite::Update(GameManager* manager)
{

}

void TestSprite::Draw(GameManager* manager)
{
	//start frame
	_renderManager->StartFrame();

	//clear screen
	_renderManager->ClearScreen();

	//transform
	angle += 0.05f;
	alphaScale += scaleFactor;
	position += positionFactor;

	if (position > 144)
	{
		position = 0;
	}

	if (alphaScale > 1.0f)
	{
		scaleFactor = -0.01f;
	}

	if (alphaScale < 0.0f)
	{
		scaleFactor = 0.01f;
	}

	//background
	for (int i = 0; i < _renderManager->GetWidth() + 144; i += 144)
	{
		_background->SetPosition(glm::vec2(i - position, _renderManager->GetHeight() / 2));
		_background->Draw(_projection);
	}	

	//_warning->SetAngle(angle);
	_warning->SetSolor(glm::vec4(1.0f, 1.0f, 1.0f, alphaScale));
	_warning->Draw(_projection);

	//title
	_title->Draw(_projection);

	//draw test info
	TestHelper::Instance()->ShowInfoText();

	//end frame
	_renderManager->EndFrame();
}