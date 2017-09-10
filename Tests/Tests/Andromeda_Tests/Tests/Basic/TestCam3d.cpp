#include "TestCam3d.h"

#include "../TestHelper.h"
#include "../InputHelper.h"

void TestCam3d::Init()
{
	_renderManager = RenderManager::Instance();
	_shaderManager = ShaderManager::Instance();
	_textureManager = TextureManager::Instance();

	//load shader
 	_shader = _shaderManager->LoadFromFile("simple", "Assets/Shaders/vertex_color_texture_transform_3d", "Assets/Shaders/vertex_color_texture", TextureColor);

	//load texture
	_texture = _textureManager->LoadFromFile("Assets/Images/wall.png");

	//create data buffer object
	_arrayObject = _renderManager->CreateVertexArrayObject(TextureColor, StaticDraw);

	//create vertices
	_arrayObject->CreateVertices(36);

	//get vertices
	TextureColorVertex* _simpleData = static_cast<TextureColorVertex*>(_arrayObject->GetVertices());

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
	for (int i = 0; i < 36;i++)
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
	_arrayObject->CreateIndices(36);

	//get indices
	unsigned short* _indices = static_cast<unsigned short*>(_arrayObject->GetIndices());

	//set data
	for (int i = 0; i < 36; i++)
	{
		_indices[i] = i;
	}	

	//generate buffer object
	_arrayObject->Generate();

	//add positions
	_cubePositions.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
	_cubePositions.push_back(glm::vec3(2.0f, 5.0f, -15.0f));
	_cubePositions.push_back(glm::vec3(-1.5f, -2.2f, -2.5f));
	_cubePositions.push_back(glm::vec3(-3.8f, -2.0f, -12.3f));
	_cubePositions.push_back(glm::vec3(2.4f, -0.4f, -3.5f));
	_cubePositions.push_back(glm::vec3(-1.7f, 3.0f, -7.5f));
	_cubePositions.push_back(glm::vec3(1.3f, -2.0f, -2.5f));
	_cubePositions.push_back(glm::vec3(1.5f, 2.0f, -2.5f));
	_cubePositions.push_back(glm::vec3(1.5f, 0.2f, -1.5f));
	_cubePositions.push_back(glm::vec3(-1.3f, 1.0f, -1.5f));

	//cam
	_cam = new Camera3d(glm::vec3(0.0f, 0.0f, 4.0f),glm::vec3(0.0f, 1.0f, 0.0f),-90.0f,0.0f);

	//
	_projection = glm::perspective(45.0f, (float)_renderManager->GetWidth() / (float)_renderManager->GetHeight(), 0.1f, 100.0f);

	_renderManager->SetDepth(true);

	_dt = 0;
	_timer = new Timer();
}

void TestCam3d::Enter()
{

}

void TestCam3d::CleanUp()
{
	delete _cam;
	delete _timer;
	delete _arrayObject;

	_cubePositions.clear();

	_textureManager->RemoveAll();
	_shaderManager->RemoveAll();

}

void TestCam3d::Pause()
{

}

void TestCam3d::Resume()
{

}

void TestCam3d::GamePause()
{

}

void TestCam3d::GameResume()
{

}

void TestCam3d::HandleEvents(GameManager* manager)
{
	//update cam
	if (InputHelper::Instance()->ActionHold(InputAction::Up))
		_cam->ProcessKeyboard(Camera3d::CameraMovementEnum::FORWARD, _dt);
	if (InputHelper::Instance()->ActionHold(InputAction::Down))
		_cam->ProcessKeyboard(Camera3d::CameraMovementEnum::BACKWARD, _dt);
	if (InputHelper::Instance()->ActionHold(InputAction::Left))
		_cam->ProcessKeyboard(Camera3d::CameraMovementEnum::LEFT, _dt);
	if (InputHelper::Instance()->ActionHold(InputAction::Right))
		_cam->ProcessKeyboard(Camera3d::CameraMovementEnum::RIGHT, _dt);

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

void TestCam3d::Update(GameManager* manager)
{
	_dt = _timer->GetDelta();
}

void TestCam3d::Draw(GameManager* manager)
{
	//start frame
	_renderManager->StartFrame();

	//clear screen
	_renderManager->ClearScreen();

	//use texture
	_renderManager->UseTexture(_texture);

	//use shader
	_shader->Bind();

	//transform

  	for (int i = 0; i < _cubePositions.size();i++)
	{
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 mvp;

		model = glm::translate(model, _cubePositions[i]);
		float angle = 20.0f * i;
		model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));

		//get view matrix from camera
		view = _cam->GetViewMatrix();

		mvp = _projection * view * model;

		_shader->SetUniform(VertexShader, "mvp", mvp);

		_arrayObject->Draw();
	}

	//end frame
	_renderManager->EndFrame();
}