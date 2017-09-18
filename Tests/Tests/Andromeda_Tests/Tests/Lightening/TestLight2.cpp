//diffuse light
#include "TestLight2.h"
#include <glm/gtc/matrix_inverse.hpp>

#include "../TestHelper.h"
#include "../InputHelper.h"


void TestLight2::Init()
{
	_renderManager = RenderManager::Instance();
	_shaderManager = ShaderManager::Instance();
	_textureManager = TextureManager::Instance();

	//load shader
	_shader = _shaderManager->LoadFromFile("model", "Assets/Shaders/lightening2_diffuse", "Assets/Shaders/lightening2_diffuse", TextureNormal);
	_lampShader = _shaderManager->LoadFromFile("lamp", "Assets/Shaders/lightening1_lamp", "Assets/Shaders/lightening1_lamp", TextureNormal);

	_cube = new ModelObj();
	_lamp = new ModelObj();
	
	_cube->LoadBinary("Assets/Models/Obj/cube.objb");
	_lamp->LoadBinary("Assets/Models/Obj/sphere.objb");

	_cube->SetShader(_shader);
	_lamp->SetShader(_lampShader);
	
	//set cube color
	_cube->SetColor(glm::vec4(1.0f, 0.5f, 0.31f,1.0f));

	//set lamp color
	_lamp->SetColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	//set lamp posistion and scale
	_lamp->SetPosition(glm::vec3(1.2f, 1.0f, 2.0f));
	_lamp->SetScale(glm::vec3(0.2f, 0.2f, 0.2f));

	//cam
	_cam = new Camera3d(glm::vec3(0.0f, 0.0f, 4.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);

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

	_rotation = 0.0f;

	_timer = new Timer();

}

void TestLight2::Enter()
{

}

void TestLight2::CleanUp()
{
	delete _cube;
	delete _lamp;

	delete _cam;
	delete _timer;

	_shaderManager->Remove(_shader);
	_shaderManager->Remove(_lampShader);
}

void TestLight2::Pause()
{

}

void TestLight2::Resume()
{

}

void TestLight2::GamePause()
{

}

void TestLight2::GameResume()
{

}

void TestLight2::HandleEvents(GameManager* manager)
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

		if (_keyboard->KeyDown(Key::M))
		{

		}
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

void TestLight2::Update(GameManager* manager)
{
	_dt = _timer->GetDelta();
	_rotation += _dt;

	//_cube->SetRotationn(glm::vec3(0.0f, _rotation,0.0f));
}

void TestLight2::Draw(GameManager* manager)
{
	//start frame
	_renderManager->StartFrame();

	//clear screen
	_renderManager->ClearScreen();

	//get view matrix from camera
	glm::mat4 view = _cam->GetViewMatrix();

	//draw cube
	{
		glm::mat4 model = _cube->GetModelMatrix();
		glm::mat3 modelInverse = glm::inverseTranspose(glm::mat3(model));
		glm::mat4 mvp = _projection * view * model;

		glm::vec4 cubeColor = _cube->GetColor();
		glm::vec3 lightPos = _lamp->GetPosition();
		glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

		//use shader
		_cube->GetShader()->Bind();

		//set uniform in shader
		_cube->GetShader()->SetUniform(VertexShader, "mvp", mvp);
		_cube->GetShader()->SetUniform(VertexShader, "model", model);
		_cube->GetShader()->SetUniform(VertexShader, "modelInverse", modelInverse);

		_cube->GetShader()->SetUniform(FragmentShader, "colors", cubeColor);
		_cube->GetShader()->SetUniform(FragmentShader, "lightPos", lightPos);
		_cube->GetShader()->SetUniform(FragmentShader, "lightColor", lightColor);

		_cube->Draw();
	}

	//draw lamp
	{
		glm::mat4 mvp = _projection * view * _lamp->GetModelMatrix();
		glm::vec4 lampColor = _lamp->GetColor();

		//use shader
		_lamp->GetShader()->Bind();

		//set uniform in shader
		_lamp->GetShader()->SetUniform(VertexShader, "mvp", mvp);
		_lamp->GetShader()->SetUniform(FragmentShader, "colors", lampColor);

		_lamp->Draw();
	}

	//draw test info
	TestHelper::Instance()->ShowInfoText();

	//end frame
	_renderManager->EndFrame();
}