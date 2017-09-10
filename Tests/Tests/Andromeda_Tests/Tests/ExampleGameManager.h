#ifndef ExampleGameManager_h
#define ExampleGameManager_h


#include <Andromeda/System/GameManager.h>


class ExampleGameManager : public Andromeda::System::GameManager
{
private:

	Andromeda::System::GameState* exampleState;

public:

	void Configure();
	void Init();
	void CleanUp();
};

#endif