#include <Andromeda/System/GameState.h>
#include <Andromeda/System/GameManager.h>

#include <Andromeda/Graphics/RenderManager.h>


using namespace Andromeda::System;
using namespace Andromeda::Graphics;

class VitaTest : public GameState
{
private:

	//render manager
	RenderManager* _renderManager;

public:

	void Init();
	void Enter();
	void CleanUp();

	void Pause();
	void Resume();

	void GamePause();
	void GameResume();

	void HandleEvents(GameManager* manager);
	void Update(GameManager* manager);
	void Draw(GameManager* manager);
};