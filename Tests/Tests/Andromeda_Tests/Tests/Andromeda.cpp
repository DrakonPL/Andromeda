#include <Andromeda/System/GameManager.h>
#include <Andromeda/System/GameLoader.h>
#include "ExampleGameManager.h"

using namespace Andromeda::System;

int main(int argc, char *argv[]) 
{
	ExampleGameManager* exampleGame = new ExampleGameManager();
	GameLoader* loader = GameLoader::Create(exampleGame);

	loader->Run();

	return 0;
}
