#include <Andromeda/System/GameState.h>
#include <Andromeda/System/GameManager.h>

#include <Andromeda/Graphics/RenderManager.h>
#include <Andromeda/Graphics/ShaderManager.h>
#include <Andromeda/Graphics/Shader.h>
#include <Andromeda/Graphics/TextureManager.h>
#include <Andromeda/Graphics/FrameBufferObject.h>
#include <Andromeda/Graphics/Sprite.h>

#include <Andromeda/Graphics/Text/TextureAtlas.h>
#include <Andromeda/Graphics/Text/TexturedFont.h>

using namespace Andromeda::System;
using namespace Andromeda::Graphics;

class TestToTexture : public GameState
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

	//frame object
	FrameBufferObject* _frameObject;

	//atlas
	TextureAtlas* _atlas;

	//font
	TexturedFont* _font;

	Shader* _fontShader;

	// Shaders
	Shader* _shader;
	Shader* _spriteShader;

	//texture
	Texture* _texture;
	Texture* _fontTexture;

	Sprite* _background;

	//transform
	float angle = 0.0f;
	float scale = 0.5f;
	float scaleFactor = 0.01f;

	glm::mat4 view;
	glm::mat4 projection;


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