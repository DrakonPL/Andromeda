#ifndef TestHelper_H
#define TestHelper_H

#include <vector>

#include <Andromeda/System/GameManager.h>
#include <Andromeda/System/GameState.h>

#include <Andromeda/Graphics/Text/TextureAtlas.h>
#include <Andromeda/Graphics/Text/TexturedFont.h>

using namespace Andromeda::Graphics;
using namespace Andromeda::System;

class TestHelper
{
private:

	static TestHelper* _testHelper;

	std::vector<GameState*> _tests;

	int _currentTest;

	//font
	TextureAtlas* _fontatlas;
	TexturedFont* _font;
	Shader* _fontShader;
	int _infoLine;

private:

	TestHelper();

public:

	static TestHelper* Instance();
	~TestHelper();

	void NextTest(GameManager* gameManager);
	GameState* GetCurrentTest();

	void AddInfoText(std::string info);
	void ShowInfoText();

};

#endif