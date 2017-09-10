#include "TestHelper.h"

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

	_tests.push_back(new TestToTexture());

	_tests.push_back(new TestLight1());
	_tests.push_back(new TestLight2());
	_tests.push_back(new TestLight3());

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