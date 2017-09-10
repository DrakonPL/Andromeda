#include <Andromeda/System/GameState.h>
#include <Andromeda/System/GameManager.h>

#include <Andromeda/Graphics/RenderManager.h>
#include <Andromeda/Graphics/ShaderManager.h>
#include <Andromeda/Graphics/Shader.h>
#include <Andromeda/Graphics/GraphicsEnums.h>
#include <Andromeda/Graphics/VertexTypes.h>
#include <Andromeda/Graphics/TextureManager.h>
#include <Andromeda/Graphics/Sprite.h>

using namespace Andromeda::System;
using namespace Andromeda::Graphics;

class TestSprite : public GameState
{
private:

	//render manager
	RenderManager* _renderManager;

	//shader manager
	ShaderManager* _shaderManager;

	//texture manager
	TextureManager* _textureManager;

	//shader
	Shader* _shader;

	//texture
	Texture* _texture;
	Texture* _warningTexture;
	Texture* _boxTexture;

	//sprites
	Sprite* _warning;
	Sprite* _title;
	Sprite* _background;

	//transform
	
	float angle = 0.0f;

	float scale = 0.5f;

	float alphaScale = 1.0f;
	float scaleFactor = 0.01f;

	float position = 0;
	float positionFactor = 1.5f;

	glm::mat4 _projection;

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