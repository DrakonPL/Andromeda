#ifndef GameState_H
#define GameState_H

#include <Andromeda/System/GameManager.h>

namespace Andromeda
{
	namespace System
	{
		class GameState
		{
		public:
			virtual void Init() = 0;
			virtual void Enter() = 0;
			virtual void CleanUp() = 0;

			virtual void Pause() = 0;
			virtual void Resume() = 0;

			virtual void GamePause() = 0;
			virtual void GameResume() = 0;

			virtual void HandleEvents(GameManager* manager) = 0;
			virtual void Update(GameManager* manager) = 0;
			virtual void Draw(GameManager* manager) = 0;

			void ChangeState(GameManager* manager, GameState* state);

		protected:
			GameState() { }

		public:
			virtual ~GameState();
		};
	}
}

#endif