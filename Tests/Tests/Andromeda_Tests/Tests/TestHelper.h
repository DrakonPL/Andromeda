#ifndef TestHelper_H
#define TestHelper_H

#include <vector>

#include <Andromeda/System/GameManager.h>
#include <Andromeda/System/GameState.h>

using namespace Andromeda::System;

class TestHelper
{
private:

	static TestHelper* _testHelper;

	std::vector<GameState*> _tests;

	int _currentTest;

private:

	TestHelper();

public:

	static TestHelper* Instance();

	void NextTest(GameManager* gameManager);
	GameState* GetCurrentTest();

};

#endif