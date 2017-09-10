#include <Andromeda/System/GameState.h>
#include <Andromeda/System/GameManager.h>

#include <Andromeda/Graphics/RenderManager.h>
#include <Andromeda/Graphics/Camera3d.h>
#include <Andromeda/Graphics/ShaderManager.h>
#include <Andromeda/Graphics/Shader.h>
#include <Andromeda/Graphics/GraphicsEnums.h>
#include <Andromeda/Graphics/VertexTypes.h>
#include <Andromeda/Graphics/TextureManager.h>
#include <Andromeda/System/Timer.h>

using namespace Andromeda::System;
using namespace Andromeda::Graphics;

class TestCam3d : public GameState
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

	//cam
	Camera3d* _cam;

	//timer
	Timer* _timer;
	float _dt;

	//transform
	std::vector<glm::vec3> _cubePositions;

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