#include <Andromeda/System/GameState.h>
#include <Andromeda/System/GameManager.h>

#include <Andromeda/Graphics/RenderManager.h>
#include <Andromeda/Graphics/Camera3d.h>
#include <Andromeda/Graphics/ShaderManager.h>
#include <Andromeda/Graphics/Shader.h>
#include <Andromeda/Graphics/GraphicsEnums.h>
#include <Andromeda/Graphics/VertexTypes.h>
#include <Andromeda/Graphics/TextureManager.h>
#include <Andromeda/Graphics/Models/ModelObj.h>
#include <Andromeda/System/Timer.h>
#include <Andromeda/Input/KeyboardDevice.h>
#include <Andromeda/Input/InputManager.h>



using namespace Andromeda::System;
using namespace Andromeda::Graphics;
using namespace Andromeda::Input;

class TestLight3 : public GameState
{
private:

	//render manager
	RenderManager* _renderManager;

	//shader manager
	ShaderManager* _shaderManager;

	//texture manager
	TextureManager* _textureManager;

	// Shaders
	Shader* _shader;
	Shader* _lampShader;

	//model
	ModelObj* _cube;
	ModelObj* _lamp;

	//cam
	Camera3d* _cam;

	bool _useMouse;
	bool _firstMouse;
	int moveX;
	int moveY;

	float _rotation;

	//timer
	Timer* _timer;
	float _dt;

	//transform
	glm::mat4 _projection;

	//input
	InputManager* _inputManager;
	KeyboardDevice* _keyboard;
	GamepadDevice* _gamepad;
	MouseDevice* _mouse;

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