#ifndef GameManager_H
#define GameManager_H

#include <vector>

namespace Andromeda
{
	namespace System
	{
		class GameState;

		class GameManager
		{
		protected:

			std::vector<GameState*> _states;
			bool _running;

		public:

			GameManager();
			~GameManager();

			virtual void Configure() = 0;
			virtual void Init() = 0;
			virtual void CleanUp() = 0;

			void ChangeState(GameState* state);
			void PushState(GameState* state);
			void PopState();

			void GamePause();
			void GameResume();

			void HandleEvents();
			void Update();
			void Draw();

			bool Running() { return _running; }
			void Quit() { _running = false; }
		};
	}
}

#endif