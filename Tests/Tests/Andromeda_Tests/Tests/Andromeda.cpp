#include <Andromeda/System/GameManager.h>
#include <Andromeda/System/GameLoader.h>
#include "ExampleGameManager.h"

using namespace Andromeda::System;

//test
int _newlib_heap_size_user = 192 * 1024 * 1024;

int main(int argc, char *argv[]) 
{
	ExampleGameManager* exampleGame = new ExampleGameManager();
	GameLoader* loader = GameLoader::Create(exampleGame);

	loader->Run();

	return 0;
}
