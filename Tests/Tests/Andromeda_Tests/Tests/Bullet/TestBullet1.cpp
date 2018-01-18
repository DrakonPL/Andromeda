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

	//textures
	_cubeTexture = _textureManager->LoadFromFile("Assets/Images/container.png", Andromeda::Graphics::TextureFilerType::LinearFilter, Andromeda::Graphics::TextureColorType::Texture_RGBA, Andromeda::Graphics::TextureWrapType::Repeat);
	_floorTexture = _textureManager->LoadFromFile("Assets/Images/wood.png",Andromeda::Graphics::TextureFilerType::LinearFilter, Andromeda::Graphics::TextureColorType::Texture_RGBA, Andromeda::Graphics::TextureWrapType::Repeat,7);

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

	InitModels();
	InitPhysic();

	_timer = new Timer();
}

void TestBullet1::InitModels()
{
	//init cube model
	{
		//create data buffer object
		_cubeModel = _renderManager->CreateVertexArrayObject(TextureColor, StaticDraw);

		//create vertices
		_cubeModel->CreateVertices(36);

		//get vertices
		TextureColorVertex* _simpleData = static_cast<TextureColorVertex*>(_cubeModel->GetVertices());

		//position
		_simpleData[0].x = -0.5f;	_simpleData[0].y = -0.5f;	_simpleData[0].z = -0.5f;
		_simpleData[1].x = 0.5f;	_simpleData[1].y = -0.5f;	_simpleData[1].z = -0.5f;
		_simpleData[2].x = 0.5f;	_simpleData[2].y = 0.5f;	_simpleData[2].z = -0.5f;
		_simpleData[3].x = 0.5f;	_simpleData[3].y = 0.5f;	_simpleData[3].z = -0.5f;
		_simpleData[4].x = -0.5f;	_simpleData[4].y = 0.5f;	_simpleData[4].z = -0.5f;
		_simpleData[5].x = -0.5f;	_simpleData[5].y = -0.5f;	_simpleData[5].z = -0.5f;

		_simpleData[6].x = -0.5f;	_simpleData[6].y = -0.5f;	_simpleData[6].z = 0.5f;
		_simpleData[7].x = 0.5f;	_simpleData[7].y = -0.5f;	_simpleData[7].z = 0.5f;
		_simpleData[8].x = 0.5f;	_simpleData[8].y = 0.5f;	_simpleData[8].z = 0.5f;
		_simpleData[9].x = 0.5f;	_simpleData[9].y = 0.5f;	_simpleData[9].z = 0.5f;
		_simpleData[10].x = -0.5f;	_simpleData[10].y = 0.5f;	_simpleData[10].z = 0.5f;
		_simpleData[11].x = -0.5f;	_simpleData[11].y = -0.5f;	_simpleData[11].z = 0.5f;

		_simpleData[12].x = -0.5f;	_simpleData[12].y = 0.5f;	_simpleData[12].z = 0.5f;
		_simpleData[13].x = -0.5f;	_simpleData[13].y = 0.5f;	_simpleData[13].z = -0.5f;
		_simpleData[14].x = -0.5f;	_simpleData[14].y = -0.5f;	_simpleData[14].z = -0.5f;
		_simpleData[15].x = -0.5f;	_simpleData[15].y = -0.5f;	_simpleData[15].z = -0.5f;
		_simpleData[16].x = -0.5f;	_simpleData[16].y = -0.5f;	_simpleData[16].z = 0.5f;
		_simpleData[17].x = -0.5f;	_simpleData[17].y = 0.5f;	_simpleData[17].z = 0.5f;

		_simpleData[18].x = 0.5f;	_simpleData[18].y = 0.5f;	_simpleData[18].z = 0.5f;
		_simpleData[19].x = 0.5f;	_simpleData[19].y = 0.5f;	_simpleData[19].z = -0.5f;
		_simpleData[20].x = 0.5f;	_simpleData[20].y = -0.5f;	_simpleData[20].z = -0.5f;
		_simpleData[21].x = 0.5f;	_simpleData[21].y = -0.5f;	_simpleData[21].z = -0.5f;
		_simpleData[22].x = 0.5f;	_simpleData[22].y = -0.5f;	_simpleData[22].z = 0.5f;
		_simpleData[23].x = 0.5f;	_simpleData[23].y = 0.5f;	_simpleData[23].z = 0.5f;

		_simpleData[24].x = -0.5f;	_simpleData[24].y = -0.5f;	_simpleData[24].z = -0.5f;
		_simpleData[25].x = 0.5f;	_simpleData[25].y = -0.5f;	_simpleData[25].z = -0.5f;
		_simpleData[26].x = 0.5f;	_simpleData[26].y = -0.5f;	_simpleData[26].z = 0.5f;
		_simpleData[27].x = 0.5f;	_simpleData[27].y = -0.5f;	_simpleData[27].z = 0.5f;
		_simpleData[28].x = -0.5f;	_simpleData[28].y = -0.5f;	_simpleData[28].z = 0.5f;
		_simpleData[29].x = -0.5f;	_simpleData[29].y = -0.5f;	_simpleData[29].z = -0.5f;

		_simpleData[30].x = -0.5f;	_simpleData[30].y = 0.5f;	_simpleData[30].z = -0.5f;
		_simpleData[31].x = 0.5f;	_simpleData[31].y = 0.5f;	_simpleData[31].z = -0.5f;
		_simpleData[32].x = 0.5f;	_simpleData[32].y = 0.5f;	_simpleData[32].z = 0.5f;
		_simpleData[33].x = 0.5f;	_simpleData[33].y = 0.5f;	_simpleData[33].z = 0.5f;
		_simpleData[34].x = -0.5f;	_simpleData[34].y = 0.5f;	_simpleData[34].z = 0.5f;
		_simpleData[35].x = -0.5f;	_simpleData[35].y = 0.5f;	_simpleData[35].z = -0.5f;

		//color
		for (int i = 0; i < 36; i++)
		{
			_simpleData[i].r = 1.0f;	_simpleData[i].g = 1.0f;	_simpleData[i].b = 1.0f;
		}

		//texture
		_simpleData[0].u = 0.0f;	_simpleData[0].v = 0.0f;
		_simpleData[1].u = 1.0f;	_simpleData[1].v = 0.0f;
		_simpleData[2].u = 1.0f;	_simpleData[2].v = 1.0f;
		_simpleData[3].u = 1.0f;	_simpleData[3].v = 1.0f;
		_simpleData[4].u = 0.0f;	_simpleData[4].v = 1.0f;
		_simpleData[5].u = 0.0f;	_simpleData[5].v = 0.0f;

		_simpleData[6].u = 0.0f;	_simpleData[6].v = 0.0f;
		_simpleData[7].u = 1.0f;	_simpleData[7].v = 0.0f;
		_simpleData[8].u = 1.0f;	_simpleData[8].v = 1.0f;
		_simpleData[9].u = 1.0f;	_simpleData[9].v = 1.0f;
		_simpleData[10].u = 0.0f;	_simpleData[10].v = 1.0f;
		_simpleData[11].u = 0.0f;	_simpleData[11].v = 0.0f;

		_simpleData[12].u = 1.0f;	_simpleData[12].v = 0.0f;
		_simpleData[13].u = 1.0f;	_simpleData[13].v = 1.0f;
		_simpleData[14].u = 0.0f;	_simpleData[14].v = 1.0f;
		_simpleData[15].u = 0.0f;	_simpleData[15].v = 1.0f;
		_simpleData[16].u = 0.0f;	_simpleData[16].v = 0.0f;
		_simpleData[17].u = 1.0f;	_simpleData[17].v = 0.0f;

		_simpleData[18].u = 1.0f;	_simpleData[18].v = 0.0f;
		_simpleData[19].u = 1.0f;	_simpleData[19].v = 1.0f;
		_simpleData[20].u = 0.0f;	_simpleData[20].v = 1.0f;
		_simpleData[21].u = 0.0f;	_simpleData[21].v = 1.0f;
		_simpleData[22].u = 0.0f;	_simpleData[22].v = 0.0f;
		_simpleData[23].u = 1.0f;	_simpleData[23].v = 0.0f;

		_simpleData[24].u = 0.0f;	_simpleData[24].v = 1.0f;
		_simpleData[25].u = 1.0f;	_simpleData[25].v = 1.0f;
		_simpleData[26].u = 1.0f;	_simpleData[26].v = 0.0f;
		_simpleData[27].u = 1.0f;	_simpleData[27].v = 0.0f;
		_simpleData[28].u = 0.0f;	_simpleData[28].v = 0.0f;
		_simpleData[29].u = 0.0f;	_simpleData[29].v = 1.0f;

		_simpleData[30].u = 0.0f;	_simpleData[30].v = 1.0f;
		_simpleData[31].u = 1.0f;	_simpleData[31].v = 1.0f;
		_simpleData[32].u = 1.0f;	_simpleData[32].v = 0.0f;
		_simpleData[33].u = 1.0f;	_simpleData[33].v = 0.0f;
		_simpleData[34].u = 0.0f;	_simpleData[34].v = 0.0f;
		_simpleData[35].u = 0.0f;	_simpleData[35].v = 1.0f;


		//create indices
		_cubeModel->CreateIndices(36);

		//get indices
		unsigned short* _indices = static_cast<unsigned short*>(_cubeModel->GetIndices());

		//set data
		for (int i = 0; i < 36; i++)
		{
			_indices[i] = i;
		}

		//generate buffer object
		_cubeModel->Generate();
	}

	//create floor model
	{
		//create data buffer object
		_floorModel = _renderManager->CreateVertexArrayObject(TextureColor, StaticDraw);

		//create vertices
		_floorModel->CreateVertices(6);

		//get vertices
		TextureColorVertex* _simpleData = static_cast<TextureColorVertex*>(_floorModel->GetVertices());

		//position
		_simpleData[0].x = -50.5f;	_simpleData[0].y = 0.0f;	_simpleData[0].z = -50.5f;
		_simpleData[1].x = 50.5f;	_simpleData[1].y = 0.0f;	_simpleData[1].z = -50.5f;
		_simpleData[2].x = 50.5f;	_simpleData[2].y = 0.0f;	_simpleData[2].z = 50.5f;
		_simpleData[3].x = 50.5f;	_simpleData[3].y = 0.0f;	_simpleData[3].z = 50.5f;
		_simpleData[4].x = -50.5f;	_simpleData[4].y = 0.0f;	_simpleData[4].z = 50.5f;
		_simpleData[5].x = -50.5f;	_simpleData[5].y = 0.0f;	_simpleData[5].z = -50.5f;

		//color
		for (int i = 0; i < 6; i++)
		{
			_simpleData[i].r = 1.0f;	_simpleData[i].g = 1.0f;	_simpleData[i].b = 1.0f;
		}

		//texture
		_simpleData[0].u = 0.0f;	_simpleData[0].v = 25.0f;
		_simpleData[1].u = 25.0f;	_simpleData[1].v = 25.0f;
		_simpleData[2].u = 25.0f;	_simpleData[2].v = 0.0f;
		_simpleData[3].u = 25.0f;	_simpleData[3].v = 0.0f;
		_simpleData[4].u = 0.0f;	_simpleData[4].v = 0.0f;
		_simpleData[5].u = 0.0f;	_simpleData[5].v = 25.0f;

		//create indices
		_floorModel->CreateIndices(6);

		//get indices
		unsigned short* _indices = static_cast<unsigned short*>(_floorModel->GetIndices());

		//set data
		for (int i = 0; i < 6; i++)
		{
			_indices[i] = i;
		}

		//generate buffer object
		_floorModel->Generate();
	}
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
		physGroundShape = new btBoxShape(btVector3(btScalar(50.0f), btScalar(0.5f), btScalar(50.0f)));

		// Set the position for the ground shape
		btTransform groundTransform;
		groundTransform.setIdentity();
		groundTransform.setOrigin(btVector3(0, -0.5f, 0));

		// Create MotionState and RigidBody object for the ground shape
		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);

		float mass = 0;
		btVector3 localInertia(0, 0, 0);

		physGroundShape->calculateLocalInertia(mass, localInertia);
		physGroundBody = new btRigidBody(mass, myMotionState, physGroundShape, localInertia);

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
	delete _cubeModel;
	delete _floorModel;

	delete _cam;
	delete _timer;

	//remove textures
	_textureManager->Remove(_cubeTexture);
	_textureManager->Remove(_floorTexture);

	//remove shader
	_shaderManager->Remove(_shader);

	//bullet
	physDynamicsWorld->removeRigidBody(physBoxBody);
	physDynamicsWorld->removeRigidBody(physGroundBody);

	delete physBoxBody->getMotionState();
	delete physGroundBody->getMotionState();

	delete physDynamicsWorld;
	delete physBroadphase;
	delete physDispatcher;
	delete physSolver;
	delete physCollisionConfiguration;

	delete physBoxShape;
	delete physBoxBody;

	delete physGroundShape;
	delete physGroundBody;
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

	//use shader
	_shader->Bind();

	//use texture
	_renderManager->UseTexture(_floorTexture);

	//draw floor
	{
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 mvp;

		//get view matrix from camera
		view = _cam->GetViewMatrix();

		//
		mvp = _projection * view * model;

		_shader->SetUniform(VertexShader, "mvp", mvp);

		_floorModel->Draw();
	}

	//use texture
	_renderManager->UseTexture(_cubeTexture);

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

		_cubeModel->Draw();
	}

	//draw test info
	TestHelper::Instance()->AddInfoText("Bullet and mipmapping test. " + std::to_string(1.0f/_dt));
	TestHelper::Instance()->ShowInfoText();

	//end frame
	_renderManager->EndFrame();
}
