#include <Andromeda/System/GameState.h>

namespace Andromeda
{
	namespace System
	{
		void GameState::ChangeState(GameManager* manager, GameState* state)
		{
			manager->ChangeState(state);
		}

		GameState::~GameState()
		{

		}
	}
}
