#include "TestHelper.h"
#include "InputHelper.h"

#include "FreeTypeTests/TestFreeTypeFont.h"
#include "FreeTypeTests/TestFreeTypeAtlas.h"

#include "Basic/TestSprite.h"
#include "Basic/TestCam3d.h"

#include "Basic/TestToTexture.h"

#include "Basic/Test1.h"
#include "Basic/Test2.h"
#include "Basic/Test3.h"
#include "Basic/Test4.h"
#include "Basic/Test5.h"
#include "Basic/Test6.h"

#include "Models/TestObjModel.h"

#include "Input/TouchTest.h"

#include "Lightening/TestLight1.h"
#include "Lightening/TestLight2.h"
#include "Lightening/TestLight3.h"
#include "Lightening/TestLight4.h"

#include <Andromeda/Graphics/ShaderManager.h>
#include <Andromeda/Graphics/RenderManager.h>

TestHelper* TestHelper::_testHelper = NULL;

TestHelper* TestHelper::Instance()
{
	if (_testHelper == NULL)
	{
		_testHelper = new TestHelper();
	}

	return _testHelper;
}

TestHelper::TestHelper()
{
	_currentTest = 0;

	_tests.push_back(new TestFreeTypeFont());
	_tests.push_back(new TestFreeTypeAtlas());

	_tests.push_back(new Test1());
	_tests.push_back(new Test2());
	_tests.push_back(new Test3());
	_tests.push_back(new Test4());
	_tests.push_back(new Test5());
	_tests.push_back(new Test6());

	_tests.push_back(new TouchTest());

	_tests.push_back(new TestSprite());
	_tests.push_back(new TestCam3d());
	_tests.push_back(new TestObjModel());
	_tests.push_back(new TestToTexture());

	_tests.push_back(new TestLight1());
	_tests.push_back(new TestLight2());
	_tests.push_back(new TestLight3());


	//init font
	//chars to cache
	const char * cache = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

	_fontShader = Andromeda::Graphics::ShaderManager::Instance()->LoadFromFile("testfont", "Assets/Shaders/font", "Assets/Shaders/font", TextureColor);

	//common
	_fontatlas = new TextureAtlas(512, 512);

	_font = new TexturedFont(_fontatlas, 16, "Assets/Fonts/MODES.TTF");
	_font->CacheGlyphs(cache);
	_font->SetShader(_fontShader);

	_fontatlas->CreateTexture();

	_infoLine = 1;
}

TestHelper::~TestHelper()
{
	for (size_t i = 0; i < _tests.size(); i++)
	{
		delete _tests[i];
	}
}

void TestHelper::NextTest(GameManager* gameManager)
{
	_currentTest++;

	if (_currentTest >= _tests.size())
	{
		_currentTest = 0;
	}

	gameManager->ChangeState(_tests[_currentTest]);

	_tests[_currentTest]->Init();

}

GameState* TestHelper::GetCurrentTest()
{
	return _tests[_currentTest];
}

void TestHelper::AddInfoText(std::string info)
{
	_font->AddText(info, RenderManager::Instance()->GetWidth() / 2, 16 * _infoLine, glm::vec3(1.0f, 1.0f, 1.0f), FontCenter);
	_infoLine++;
}

void TestHelper::ShowInfoText()
{
	RenderManager::Instance()->SetDepth(false);

	glm::mat4 projection = glm::ortho(0.0f, (float)RenderManager::Instance()->GetWidth(), (float)RenderManager::Instance()->GetHeight(), 0.0f, -1.0f, 1.0f);

	std::string nextTest = "Press " + InputHelper::Instance()->InputName(InputAction::Next) + " to change test";

	_font->AddText(nextTest, RenderManager::Instance()->GetWidth() / 2, RenderManager::Instance()->GetHeight() - 5, glm::vec3(1.0f, 1.0f, 1.0f), FontCenter);

	_font->Draw(projection);

	RenderManager::Instance()->SetDepth(true);

	_infoLine = 1;
}

