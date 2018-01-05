#include "TestBullet1.h"

#include "../TestHelper.h"
#include "../InputHelper.h"


void TestBullet1::Init()
{
	_renderManager = RenderManager::Instance();
	_shaderManager = ShaderManager::Instance();
	_textureManager = TextureManager::Instance();

	//load shader
	_shader = _shaderManager->LoadFromFile("simple", "Assets/Shaders/vertex_color_texture_transform_3d", "Assets/Shaders/vertex_color_texture", TextureColor);

	_model = new ModelObj();
	_model->LoadBinary("Assets/Models/Obj/CompanionCube/companion_cube.objb");
	_model->SetShader(_shader);

	//cam
	_cam = new Camera3d(glm::vec3(0.0f, 1.0f, 4.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);

	//
	_projection = glm::perspective(45.0f, (float)_renderManager->GetWidth() / (float)_renderManager->GetHeight(), 0.1f, 100.0f);

	//input
	_inputManager = InputManager::Instance();

	if (_inputManager->GetKayboardCount() > 0)
		_keyboard = _inputManager->GetKeyboardDevice(0);

	if (_inputManager->GetMouseCount() > 0)
	{
		_mouse = _inputManager->GetMouseDevice(0);

		//disable cursor
		_mouse->SetCursorVisible(false);

		_useMouse = true;
		_firstMouse = true;
	}


	if (_inputManager->GetGamepadCount() > 0)
		_gamepad = _inputManager->GetGamepadDevice(0);

	InitPhysic();

	_timer = new Timer();
}

void TestBullet1::InitPhysic()
{
	btVector3 worldAabbMin(-1000, -1000, -1000);
	btVector3 worldAabbMax(1000, 1000, 1000);
	int maxProxies = 32766;

	//Collision configuration contains default setup for memory, collision setup
	physCollisionConfiguration = new btDefaultCollisionConfiguration();

	//Use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	physDispatcher = new btCollisionDispatcher(physCollisionConfiguration);
	physBroadphase = new btAxisSweep3(worldAabbMin, worldAabbMax, maxProxies);


	//The default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
	physSolver = solver;

	//Create the main physics object
	physDynamicsWorld = new btDiscreteDynamicsWorld(physDispatcher, physBroadphase, physSolver, physCollisionConfiguration);
	physDynamicsWorld->setGravity(btVector3(0, -10, 0));

	//Create the ground object
	{
		// Create the ground shape
		btCollisionShape* physGroundShape = new btBoxShape(btVector3(btScalar(50.0f), btScalar(0.5f), btScalar(50.0f)));

		// Set the position for the ground shape
		btTransform groundTransform;
		groundTransform.setIdentity();
		groundTransform.setOrigin(btVector3(0, -0.5f, 0));

		// Create MotionState and RigidBody object for the ground shape
		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);

		float mass = 0;
		btVector3 localInertia(0, 0, 0);

		physGroundShape->calculateLocalInertia(mass, localInertia);
		btRigidBody* physGroundBody = new btRigidBody(mass, myMotionState, physGroundShape, localInertia);

		// Add ground body to physics object
		physDynamicsWorld->addRigidBody(physGroundBody);
	}

	//Create the box object
	{
		//Create the box shape
		physBoxShape = new btBoxShape(btVector3(0.5, 0.5, 0.5));

		//Set mass, initial inertia and position for the box
		float mass = 1.0f;
		btVector3 inertia(0, 0, 0);
		btTransform startTransform;
		startTransform.setIdentity();
		startTransform.setOrigin(btVector3(0, 4, 0));

		//Calculate the inertia
		physBoxShape->calculateLocalInertia(mass, inertia);

		// Create MotionState and RigidBody object for the box shape
		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
		physBoxBody = new btRigidBody(mass, myMotionState, physBoxShape, inertia);

		// Add box body to physics object & activate it
		physDynamicsWorld->addRigidBody(physBoxBody);
		physBoxBody->activate();
		physBoxBody->setActivationState(DISABLE_DEACTIVATION);
	}
}

glm::mat4 TestBullet1::btScalar2glmMat4(btScalar* matrix)
{
	return glm::mat4(
		matrix[0], matrix[1], matrix[2], matrix[3],
		matrix[4], matrix[5], matrix[6], matrix[7],
		matrix[8], matrix[9], matrix[10], matrix[11],
		matrix[12], matrix[13], matrix[14], matrix[15]);
}

void TestBullet1::Enter()
{

}

void TestBullet1::CleanUp()
{
	delete _model;
	delete _cam;
	delete _timer;

	_shaderManager->Remove(_shader);
}

void TestBullet1::Pause()
{

}

void TestBullet1::Resume()
{

}

void TestBullet1::GamePause()
{

}

void TestBullet1::GameResume()
{

}

void TestBullet1::HandleEvents(GameManager* manager)
{
	if (_mouse != 0 && _useMouse)
	{
		int posx = _mouse->GetPosX();
		int posy = _mouse->GetPosY() * -1.0f;

		if (_firstMouse)
		{
			moveX = posx;
			moveY = posy;

			_firstMouse = false;
		}

		int xoffset = posx - moveX;
		int yoffset = posy - moveY;

		moveX = posx;
		moveY = posy;

		_cam->ProcessMouseMovement(xoffset, yoffset, false);
	}


	if (_keyboard != 0)
	{
		//update cam
		if (_keyboard->KeyDown(Key::W))
			_cam->ProcessKeyboard(Camera3d::CameraMovementEnum::FORWARD, _dt);
		if (_keyboard->KeyDown(Key::S))
			_cam->ProcessKeyboard(Camera3d::CameraMovementEnum::BACKWARD, _dt);
		if (_keyboard->KeyDown(Key::A))
			_cam->ProcessKeyboard(Camera3d::CameraMovementEnum::LEFT, _dt);
		if (_keyboard->KeyDown(Key::D))
			_cam->ProcessKeyboard(Camera3d::CameraMovementEnum::RIGHT, _dt);

		if (_keyboard->KeyDown(Key::Left))
			_cam->ProcessMouseMovement(-5, 0, false);
		if (_keyboard->KeyDown(Key::Right))
			_cam->ProcessMouseMovement(5, 0, false);
		if (_keyboard->KeyDown(Key::Up))
			_cam->ProcessMouseMovement(0, 5, false);
		if (_keyboard->KeyDown(Key::Down))
			_cam->ProcessMouseMovement(0, -5, false);
	}

	if (_gamepad != 0)
	{
		//update cam
		if (_gamepad->KeyDown(Gamepad::Up))
			_cam->ProcessKeyboard(Camera3d::CameraMovementEnum::FORWARD, _dt);
		if (_gamepad->KeyDown(Gamepad::Down))
			_cam->ProcessKeyboard(Camera3d::CameraMovementEnum::BACKWARD, _dt);
		if (_gamepad->KeyDown(Gamepad::Left))
			_cam->ProcessKeyboard(Camera3d::CameraMovementEnum::LEFT, _dt);
		if (_gamepad->KeyDown(Gamepad::Right))
			_cam->ProcessKeyboard(Camera3d::CameraMovementEnum::RIGHT, _dt);

		if (_gamepad->KeyDown(Gamepad::Square))
			_cam->ProcessMouseMovement(-5, 0, false);
		if (_gamepad->KeyDown(Gamepad::Circle))
			_cam->ProcessMouseMovement(5, 0, false);
		if (_gamepad->KeyDown(Gamepad::Triangle))
			_cam->ProcessMouseMovement(0, 5, false);
		if (_gamepad->KeyDown(Gamepad::Cross))
			_cam->ProcessMouseMovement(0, -5, false);
	}

	if (InputHelper::Instance()->ActionPressed(InputAction::Next))
	{
		TestHelper::Instance()->NextTest(manager);
	}

	if (InputHelper::Instance()->ActionPressed(InputAction::Exit))
	{
		manager->Quit();
	}

	InputHelper::Instance()->Update();
}

void TestBullet1::Update(GameManager* manager)
{
	_dt = _timer->GetDelta();

	//physic update
	if (physDynamicsWorld && _dt < 0.1f)
		physDynamicsWorld->stepSimulation(_dt);
}

void TestBullet1::Draw(GameManager* manager)
{
	//start frame
	_renderManager->StartFrame();

	//clear screen
	_renderManager->ClearScreen();

	//use texture
	//_renderManager->UseTexture(_texture);

	//use shader
	_shader->Bind();

	//draw box
	{
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 mvp;

		//get view matrix from camera
		view = _cam->GetViewMatrix();

		//get box matrix from bullet object
		float cubeMatrix[16];
		btTransform cubeTransform;
		physBoxBody->getMotionState()->getWorldTransform(cubeTransform);
		cubeTransform.getOpenGLMatrix((btScalar*)&cubeMatrix);

		model = btScalar2glmMat4(cubeMatrix);

		//
		mvp = _projection * view * model;

		_shader->SetUniform(VertexShader, "mvp", mvp);

		_model->Draw();
	}

	//draw test info
	TestHelper::Instance()->AddInfoText("Load OBJ Imrod model.");
	TestHelper::Instance()->ShowInfoText();

	//end frame
	_renderManager->EndFrame();
}

/*
void BulletOpenGLApplication::ShootBox(const btVector3 &direction)
{
	// create a new box object
	GameObject* pObject = CreateGameObject(new btBoxShape(btVector3(1, 1, 1)),
		1, btVector3(0.4f, 0.f, 0.4f), m_cameraPosition);

	// calculate the velocity
	btVector3 velocity = direction;
	velocity.normalize();
	velocity *= 25.0f;

	// set the linear velocity of the box
	pObject->GetRigidBody()->setLinearVelocity(velocity);
}
*/