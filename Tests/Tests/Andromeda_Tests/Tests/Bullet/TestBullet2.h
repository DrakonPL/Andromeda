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

//bullet
#include "bullet/LinearMath/btVector3.h"
#include "bullet/LinearMath/btMatrix3x3.h"
#include "bullet/LinearMath/btTransform.h"
#include "bullet/LinearMath/btQuickprof.h"
#include "bullet/LinearMath/btAlignedObjectArray.h"
#include "bullet/btBulletDynamicsCommon.h"

#include "BasicCar.h"

class TestBullet2 : public GameState
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

	//model
	ModelObj* _carModel;
	ModelObj* _wheelModel;

	VertexArrayObject* _cubeModel;
	VertexArrayObject* _floorModel;

	Texture* _floorTexture;
	Texture* _cubeTexture;

	//wheek positions
	std::vector<glm::vec3> _wheelPositions;

	//cam
	Camera3d* _cam;

	bool _useMouse;
	bool _firstMouse;
	int moveX;
	int moveY;

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

	//Bullet physics - Main objects
	btDynamicsWorld* physDynamicsWorld;
	btBroadphaseInterface* physBroadphase;
	btCollisionDispatcher* physDispatcher;
	btConstraintSolver*	physSolver;
	btDefaultCollisionConfiguration* physCollisionConfiguration;

	//Bullet physics - Scene objects
	btCollisionShape* physBoxShape;
	btRigidBody* physBoxBody;

	btCollisionShape* physGroundShape;
	btRigidBody* physGroundBody;

	//car
	BasicCar* _car;

private:

	void InitModels();
	void InitPhysic();

	glm::mat4 btScalar2glmMat4(btScalar* matrix);

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