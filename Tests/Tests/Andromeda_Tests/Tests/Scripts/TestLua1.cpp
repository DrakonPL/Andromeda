#include "TestLua1.h"

#include "../TestHelper.h"
#include "../InputHelper.h"

#include <Andromeda/Utils/Logger.h>



int marcin(int test)
{
	return test * 3;
}

void TestLua1::Init()
{
	_renderManager = RenderManager::Instance();
	_shaderManager = ShaderManager::Instance();
	_textureManager = TextureManager::Instance();

	//lua stufff
	myLuaState = luaL_newstate();

	// Connect LuaBind to this lua state
	luabind::open(myLuaState);

	luabind::module(myLuaState)
	[
		luabind::class_<Andromeda::Utils::Logger>("Logger") //Register the class
		.def("IsActive", &Andromeda::Utils::Logger::IsActive) //method to execute a lua script
		.scope
		[
			luabind::def("Instance", &Andromeda::Utils::Logger::Instance)
		]
	];

	luaL_dostring(
		myLuaState,
		"Logger.Instance():IsActive()\n"
	);

	try
	{
		AndromedaBindings* bindings = new AndromedaBindings(myLuaState);
		bindings->Bind();

		luaL_dostring(
			myLuaState,
			"TextureManager.Instance():LoadFromFile(\"Assets/Images/bird_sheet.png\",TextureFilerType.NearestFilter,TextureColorType.Texture_RGBA)\n"
		);
	}
	catch (const std::exception &TheError)
	{
		std::string erro = TheError.what();
	}



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


	//// Add our function to the state's global scope
	//luabind::module(myLuaState)
	//[
	//	luabind::def("marcin", marcin)
	//];

	//luaL_dostring(
	//	myLuaState,
	//	"marcin(123)\n"
	//);


	//// Define a lua function that we can call
	//luaL_dostring(
	//	myLuaState,
	//	"function add(first, second)\n"
	//	"  return first + second\n"
	//	"end\n"
	//);

	//int tets = luabind::call_function<int>(myLuaState, "add", 2, 3);
}

void TestLua1::Enter()
{

}

void TestLua1::CleanUp()
{
	lua_close(myLuaState);

	delete _warning;
	delete _title;
	delete _background;

	_textureManager->Remove(_texture);
	_textureManager->Remove(_warningTexture);
	_textureManager->Remove(_boxTexture);

	_shaderManager->Remove(_shader);
}

void TestLua1::Pause()
{

}

void TestLua1::Resume()
{

}

void TestLua1::GamePause()
{

}

void TestLua1::GameResume()
{

}

void TestLua1::HandleEvents(GameManager* manager)
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

void TestLua1::Update(GameManager* manager)
{

}

void TestLua1::Draw(GameManager* manager)
{
	//start frame
	_renderManager->StartFrame();

	//clear screen
	_renderManager->ClearScreen();

	_renderManager->SetDepth(false);

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
	for (int i = 0; i < _renderManager->GetWidth() + 300; i += 144)
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
	TestHelper::Instance()->AddInfoText("Drawing some sprites.");
	TestHelper::Instance()->ShowInfoText();

	//end frame
	_renderManager->EndFrame();
}