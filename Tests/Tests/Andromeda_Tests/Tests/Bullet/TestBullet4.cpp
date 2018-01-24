#include "TestBullet4.h"

#include "../TestHelper.h"
#include "../InputHelper.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Andromeda/FileSystem/FileManager.h>

using namespace Andromeda;


#include <vector>

class vecto3
{
public:

	float x, y, z;
};

void TestBullet4::Init()
{
	_renderManager = RenderManager::Instance();
	_shaderManager = ShaderManager::Instance();
	_textureManager = TextureManager::Instance();

	//load shader
	_shader = _shaderManager->LoadFromFile("simple", "Assets/Shaders/vertex_color_texture_transform_3d", "Assets/Shaders/vertex_color_texture", TextureColor);

	//cam
	_cam = new Camera3d(glm::vec3(0.0f, 4.0f, 4.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);

	//cam settings
	_cameraHeight = 2.0f;
	_minCameraDistance = 1.f;
	_maxCameraDistance = 3.f;

	//
	_projection = glm::perspective(45.0f, (float)_renderManager->GetWidth() / (float)_renderManager->GetHeight(), 0.1f, 300.0f);

	//input
	_inputManager = InputManager::Instance();

	if (_inputManager->GetKayboardCount() > 0)
		_keyboard = _inputManager->GetKeyboardDevice(0);

	if (_inputManager->GetMouseCount() > 0)
	{
		//disable cursor
		_inputManager->GetMouseDevice(0)->SetCursorVisible(false);
	}

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

	initState = 0;

	_timer = new Timer();
}

void TestBullet4::InitModels()
{
	//load car model
	_carModel = new ModelObj();
	_carModel->LoadBinary("Assets/Models/Obj/WillyKart/willy.objb");
	_carModel->SetShader(_shader);

	//load wheel model
	_wheelModel = new ModelObj();
	_wheelModel->LoadBinary("Assets/Models/Obj/WillyKart/armywheels.objb");
	_wheelModel->SetShader(_shader);

	//load map
	_mapModel = new ModelObj();
	_mapModel->LoadBinary("Assets/Models/Obj/soccer/soccer.objb");
	_mapModel->SetShader(_shader);

	//load soccer model
	_soccerModel = new ModelObj();
	_soccerModel->LoadBinary("Assets/Models/Obj/soccer_ball/soccer_ball.objb");
	_soccerModel->SetShader(_shader);
}

void TestBullet4::InitPhysic()
{
	btVector3 worldAabbMin(-1000, -1000, -1000);
	btVector3 worldAabbMax(1000, 1000, 1000);
	int maxProxies = 32766;

	//Collision configuration contains default setup for memory, collision setup
	physCollisionConfiguration = new btDefaultCollisionConfiguration();

	//Use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	physDispatcher = new btCollisionDispatcher(physCollisionConfiguration);
	physBroadphase = new btDbvtBroadphase();// btAxisSweep3(worldAabbMin, worldAabbMax, maxProxies);


	//The default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
	physSolver = solver;

	//Create the main physics object
	physDynamicsWorld = new btDiscreteDynamicsWorld(physDispatcher, physBroadphase, physSolver, physCollisionConfiguration);
	physDynamicsWorld->setGravity(btVector3(0, -10, 0));

	//create collision shape from map
	{
		//create file to write
		FileSystem::BaseFile* file = FileSystem::FileManager::Instance()->GetFile("Assets/Models/Obj/soccer/soccer.phys");
		file->Open(FileSystem::Read, FileSystem::Binary);

		//read vector count
		int vectorCount = 0;
		file->Read(&vectorCount, sizeof(int), 1);

		std::vector<vecto3> vectors;
		vectors.resize(vectorCount);

		file->Read(&vectors[0], sizeof(vecto3), vectorCount);

		file->Close();
		delete file;

		//load physic shape from this...
		btTriangleMesh* trimesh = new btTriangleMesh();

		for (size_t i = 0; i < vectorCount; i+=3)
		{
			btVector3 vec1 = btVector3(vectors[i].x, vectors[i].y, vectors[i].z);
			btVector3 vec2 = btVector3(vectors[i+1].x, vectors[i+1].y, vectors[i+1].z);
			btVector3 vec3 = btVector3(vectors[i+2].x, vectors[i+2].y, vectors[i+2].z);

			trimesh->addTriangle(vec1, vec2, vec3);
		}

		// Set the position for the ground shape
		btTransform groundTransform;
		groundTransform.setIdentity();
		groundTransform.setOrigin(btVector3(0, 0.0f, 0));

		// Create MotionState and RigidBody object for the ground shape
		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);

		float mass = 0;
		btVector3 localInertia(0, 0, 0);

		btCollisionShape* trimeshShape = new btBvhTriangleMeshShape(trimesh, true,true);

		//importart for not going thru mesh
		trimeshShape->setMargin(0.5f);
		//trimeshShape->calculateLocalInertia(mass, localInertia); //gives error

		physGroundBody = new btRigidBody(mass, myMotionState, trimeshShape, localInertia);
		//physGroundBody->setActivationState(DISABLE_DEACTIVATION);

		// Add ground body to physics object
		physDynamicsWorld->addRigidBody(physGroundBody);
	}

	//Create the box object
	{
		//Create the box shape
		physBallShape = new btSphereShape(1.0f);// btBoxShape(btVector3(0.5, 0.5, 0.5));

		//Set mass, initial inertia and position for the box
		float mass = 10.0f;
		btVector3 inertia(0, 0, 0);
		btTransform startTransform;
		startTransform.setIdentity();
		startTransform.setOrigin(btVector3(0, 4, 0));

		//Calculate the inertia
		physBallShape->calculateLocalInertia(mass, inertia);

		// Create MotionState and RigidBody object for the box shape
		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
		physBallBody = new btRigidBody(mass, myMotionState, physBallShape, inertia);

		// Add box body to physics object & activate it
		physDynamicsWorld->addRigidBody(physBallBody);
		physBallBody->activate();
		physBallBody->setActivationState(DISABLE_DEACTIVATION);
	}

	//init car
	{
		btVector3 carPos(0, 2.0f, 10);

		_car = new BasicCar();
		_car->Create(_carModel,_wheelModel,_shader, physDynamicsWorld, carPos, 650.0f);
	}
}

glm::mat4 TestBullet4::btScalar2glmMat4(btScalar* matrix)
{
	return glm::mat4(
		matrix[0], matrix[1], matrix[2], matrix[3],
		matrix[4], matrix[5], matrix[6], matrix[7],
		matrix[8], matrix[9], matrix[10], matrix[11],
		matrix[12], matrix[13], matrix[14], matrix[15]);
}

void TestBullet4::CleanUp()
{
	delete _carModel;
	delete _wheelModel;

	delete _mapModel;
	delete _soccerModel;

	delete _cam;
	delete _timer;

	//remove shader
	_shaderManager->Remove(_shader);

	//remove bullet car
	delete _car;

	//bullet
	physDynamicsWorld->removeRigidBody(physBallBody);
	physDynamicsWorld->removeRigidBody(physGroundBody);

	delete physBallBody->getMotionState();
	delete physGroundBody->getMotionState();

	delete physDynamicsWorld;
	delete physBroadphase;
	delete physDispatcher;
	delete physSolver;
	delete physCollisionConfiguration;

	delete physBallShape;
	delete physBallBody;

	delete physGroundShape;
	delete physGroundBody;
}

void TestBullet4::Pause()
{

}

void TestBullet4::Resume()
{

}

void TestBullet4::GamePause()
{

}

void TestBullet4::GameResume()
{

}

void TestBullet4::HandleEvents(GameManager* manager)
{
	//if (_mouse != 0 && _useMouse)
	//{
	//	int posx = _mouse->GetPosX();
	//	int posy = _mouse->GetPosY() * -1.0f;

	//	if (_firstMouse)
	//	{
	//		moveX = posx;
	//		moveY = posy;

	//		_firstMouse = false;
	//	}

	//	int xoffset = posx - moveX;
	//	int yoffset = posy - moveY;

	//	moveX = posx;
	//	moveY = posy;

	//	_cam->ProcessMouseMovement(xoffset, yoffset, false);
	//}


	//if (_keyboard != 0)
	//{
	//	//update cam
	//	if (_keyboard->KeyDown(Key::W))
	//		_cam->ProcessKeyboard(Camera3d::CameraMovementEnum::FORWARD, _dt);
	//	if (_keyboard->KeyDown(Key::S))
	//		_cam->ProcessKeyboard(Camera3d::CameraMovementEnum::BACKWARD, _dt);
	//	if (_keyboard->KeyDown(Key::A))
	//		_cam->ProcessKeyboard(Camera3d::CameraMovementEnum::LEFT, _dt);
	//	if (_keyboard->KeyDown(Key::D))
	//		_cam->ProcessKeyboard(Camera3d::CameraMovementEnum::RIGHT, _dt);

	//	if (_keyboard->KeyDown(Key::Left))
	//		_cam->ProcessMouseMovement(-5, 0, false);
	//	if (_keyboard->KeyDown(Key::Right))
	//		_cam->ProcessMouseMovement(5, 0, false);
	//	if (_keyboard->KeyDown(Key::Up))
	//		_cam->ProcessMouseMovement(0, 5, false);
	//	if (_keyboard->KeyDown(Key::Down))
	//		_cam->ProcessMouseMovement(0, -5, false);
	//}

	//if (_gamepad != 0)
	//{
	//	//update cam
	//	if (_gamepad->KeyDown(Gamepad::Up))
	//		_cam->ProcessKeyboard(Camera3d::CameraMovementEnum::FORWARD, _dt);
	//	if (_gamepad->KeyDown(Gamepad::Down))
	//		_cam->ProcessKeyboard(Camera3d::CameraMovementEnum::BACKWARD, _dt);
	//	if (_gamepad->KeyDown(Gamepad::Left))
	//		_cam->ProcessKeyboard(Camera3d::CameraMovementEnum::LEFT, _dt);
	//	if (_gamepad->KeyDown(Gamepad::Right))
	//		_cam->ProcessKeyboard(Camera3d::CameraMovementEnum::RIGHT, _dt);

	//	if (_gamepad->KeyDown(Gamepad::Square))
	//		_cam->ProcessMouseMovement(-5, 0, false);
	//	if (_gamepad->KeyDown(Gamepad::Circle))
	//		_cam->ProcessMouseMovement(5, 0, false);
	//	if (_gamepad->KeyDown(Gamepad::Triangle))
	//		_cam->ProcessMouseMovement(0, 5, false);
	//	if (_gamepad->KeyDown(Gamepad::Cross))
	//		_cam->ProcessMouseMovement(0, -5, false);
	//}

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

void TestBullet4::Update(GameManager* manager)
{
	_dt = _timer->GetDelta();

	//physic update
	if (physDynamicsWorld)
		physDynamicsWorld->stepSimulation(_dt,2);

	if (physDynamicsWorld)
		_car->Update(_keyboard,_gamepad,_dt);

	if (initState == 1)
	{
		InitModels();
		InitPhysic();

		initState = 2;
	}
}

void TestBullet4::Draw(GameManager* manager)
{
	//start frame
	_renderManager->StartFrame();

	//clear screen
	_renderManager->ClearScreen();

	if (initState == 2)
	{
		//use shader
		_shader->Bind();

		//camera logic
		glm::vec3 cameraTargetPosition = glm::vec3(_car->GetWorldTransform().getOrigin()[0], _car->GetWorldTransform().getOrigin()[1], _car->GetWorldTransform().getOrigin()[2]);

		_cam->Position.y = (15.0*_cam->Position.y + cameraTargetPosition.y + _cameraHeight) / 16.0;

		glm::vec3 camToObject = cameraTargetPosition - _cam->Position;

		float cameraDistance = glm::length(camToObject);
		float correctionFactor = 0.f;

		if (cameraDistance < _minCameraDistance)
		{
			correctionFactor = 0.15*(_minCameraDistance - cameraDistance) / cameraDistance;
		}
		if (cameraDistance > _maxCameraDistance)
		{
			correctionFactor = 0.15*(_maxCameraDistance - cameraDistance) / cameraDistance;
		}

		_cam->Position.x -= (correctionFactor * camToObject).x;
		_cam->Position.y -= (correctionFactor * camToObject).y;
		_cam->Position.z -= (correctionFactor * camToObject).z;

		glm::mat4 camView = glm::lookAt(_cam->Position, cameraTargetPosition, _cam->Up);

		//cam view
		//glm::mat4 camView = _cam->GetViewMatrix();

		//draw floor
		{
			glm::mat4 model;
			glm::mat4 mvp;

			//
			mvp = _projection * camView * model;

			_shader->SetUniform(VertexShader, "mvp", mvp);

			_mapModel->Draw();
		}

		//draw ball
		{
			glm::mat4 model;
			glm::mat4 mvp;

			//get box matrix from bullet object
			float cubeMatrix[16];
			btTransform cubeTransform;
			physBallBody->getMotionState()->getWorldTransform(cubeTransform);
			cubeTransform.getOpenGLMatrix((btScalar*)&cubeMatrix);

			model = btScalar2glmMat4(cubeMatrix);

			//
			mvp = _projection * camView * model;

			_shader->SetUniform(VertexShader, "mvp", mvp);

			_soccerModel->Draw();
		}


		//draw car
		{
			_car->Render(camView, _projection);
		}

		float speed = _car->GetSpeed();

		//draw test info
		TestHelper::Instance()->AddInfoText("Bullet and map test. " + std::to_string(speed));
	}
	else
	{
		TestHelper::Instance()->AddInfoText("Loading data - Please wait...");
		initState = 1;
	}

	TestHelper::Instance()->ShowInfoText();

	//end frame
	_renderManager->EndFrame();
}