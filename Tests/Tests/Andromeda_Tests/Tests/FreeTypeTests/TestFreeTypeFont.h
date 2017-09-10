#include <Andromeda/System/GameState.h>
#include <Andromeda/System/GameManager.h>

#include <Andromeda/Graphics/RenderManager.h>
#include <Andromeda/Graphics/ShaderManager.h>
#include <Andromeda/Graphics/Shader.h>
#include <Andromeda/Graphics/TextureManager.h>
#include <Andromeda/Graphics/Sprite.h>

#include <Andromeda/Graphics/Text/TextureAtlas.h>
#include <Andromeda/Graphics/Text/TexturedFont.h>

using namespace Andromeda::System;
using namespace Andromeda::Graphics;

class TestFreeTypeFont : public GameState
{
private:

	//render manager
	RenderManager* _renderManager;

	//shader manager
	ShaderManager* _shaderManager;

	//texture manager
	TextureManager* _textureManager;

	//
	TextureAtlas* _fontatlas;
	TexturedFont* _font;

	//atlas
	TextureAtlas* _atlas;

	//font
	TexturedFont* _font1;
	TexturedFont* _font2;
	TexturedFont* _font3;

	//shader
	Shader* _fontShader;

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