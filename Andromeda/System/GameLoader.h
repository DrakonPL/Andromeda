#ifndef GameLoader_H
#define GameLoader_H

#include <Andromeda/System/GameManager.h>

namespace Andromeda
{
	namespace System
	{
		class GameLoader
		{
		protected:

			GameManager* _gameManager;

		public:
			virtual ~GameLoader()
			{
			}

			GameLoader(GameManager* gameManager);

			static GameLoader* Create(GameManager* gameManager);

			virtual void Run() = 0;
		};
	}
}

#endif