#include "VitaTest.h"

#include <stdlib.h>

void VitaTest::Init()
{
	_renderManager = RenderManager::Instance();

}

void VitaTest::Enter()
{
	
}

void VitaTest::CleanUp()
{

}

void VitaTest::Pause()
{

}

void VitaTest::Resume()
{

}

void VitaTest::GamePause()
{

}

void VitaTest::GameResume()
{

}

void VitaTest::HandleEvents(GameManager* manager)
{

}

void VitaTest::Update(GameManager* manager)
{

}

void VitaTest::Draw(GameManager* manager)
{
	//start frame
	_renderManager->StartFrame();

	//clear screen
	_renderManager->ClearScreen();

	//just for test
	_renderManager->SetClearColor(RGBA8(rand() % 255, rand() % 255, rand() % 255,255));

	//end frame
	_renderManager->EndFrame();
}