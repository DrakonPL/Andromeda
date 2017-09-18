#include <Andromeda/System/GameState.h>
#include <Andromeda/System/GameManager.h>

#include <Andromeda/Graphics/RenderManager.h>
#include <Andromeda/Graphics/ShaderManager.h>
#include <Andromeda/Graphics/TextureManager.h>
#include <Andromeda/Graphics/Shader.h>
#include <Andromeda/Graphics/VertexTypes.h>

using namespace Andromeda::System;
using namespace Andromeda::Graphics;

class Test4 : public GameState
{
private:

	//render manager
	RenderManager* _renderManager;

	//shader manager
	ShaderManager* _shaderManager;

	//texture manager
	TextureManager* _textureManager;

	//vertex array
	VertexArrayObject* _arrayObject;

	// Shaders
	Shader* _shader;

	//texture
	Texture* _texture;

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