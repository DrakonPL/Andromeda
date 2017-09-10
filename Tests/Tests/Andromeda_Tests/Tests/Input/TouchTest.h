#include <Andromeda/System/GameState.h>
#include <Andromeda/System/GameManager.h>

#include <Andromeda/Graphics/RenderManager.h>
#include <Andromeda/Graphics/ShaderManager.h>
#include <Andromeda/Graphics/Shader.h>
#include <Andromeda/Graphics/GraphicsEnums.h>
#include <Andromeda/Graphics/VertexTypes.h>
#include <Andromeda/Graphics/TextureManager.h>
#include <Andromeda/Graphics/Sprite.h>
#include <Andromeda/Input/KeyboardDevice.h>
#include <Andromeda/Input/InputManager.h>

#include <Andromeda/Graphics/Text/TextureAtlas.h>
#include <Andromeda/Graphics/Text/TexturedFont.h>

using namespace Andromeda::System;
using namespace Andromeda::Graphics;
using namespace Andromeda::Input;


class TouchTest : public GameState
{
private:

	//render manager
	RenderManager* _renderManager;

	//shader manager
	ShaderManager* _shaderManager;

	//texture manager
	TextureManager* _textureManager;

	//atlas
	TextureAtlas* _atlas;

	//font
	TexturedFont* _font;

	//shader
	Shader* _shader;

	//texture
	Texture* _texture;	

	glm::mat4 _projection;

	//input
	InputManager* _inputManager;
	KeyboardDevice* _keyboard;
	GamepadDevice* _gamepad;

	TouchDevice* _frontTouch;
	TouchDevice* _backTouch;

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