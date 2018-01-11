#include "BasicCar.h"

BasicCar::BasicCar()
{
	mChassisShape = NULL;
	mCompoundShape = NULL;
	mVehicleRaycaster = NULL;
	mRaycastVehicle = NULL;

	mSteeringValue = 0.f;
	mMaxEngineForce = 3000.f; // This should be engine/velocity dependent
	mMaxBreakingForce = 100.f;
	mSteeringIncrement = 0.04f;
	mSteeringClamp = 0.4f;
	mEngineForce = 0.f;
	mBreakingForce = 0.f;

	mSuspensionStiffness = 400.0f;
	mSuspensionDamping = 100.0f;
	mSuspensionCompression = 4.2f;
	mWheelFriction = 20;//1e30f;
	mRollInfluence = 0.1f;//1.0f;

	mWheelWidth = 0.3f;
	mWheelRadius = 0.4f;

	mSize = 1.0f;
}

BasicCar::~BasicCar()
{
	Destroy();
}

bool BasicCar::Create(ModelObj* chasis, ModelObj* wheel, Shader* shader, btDynamicsWorld *dynamicsWorld, btVector3 &position, btScalar mass)
{
	//models
	_carModel = chasis;
	_wheelModel = wheel;

	//shader
	_shader = shader;

	//dynamic world
	mDynamicsWorld = dynamicsWorld;

	// create a chassis shape that is proportfion to the size	
	mChassisShape = new btBoxShape(btVector3(0.9045f, 0.5335f, 1.5355f));
	mSize = 0.7f;

	mCompoundShape = new btCompoundShape();
	//mWheelWidth = 0.4f * mSize;
	//mWheelRadius = 0.5f * mSize;

	btTransform localTrans;
	localTrans.setIdentity();
	localTrans.setOrigin(btVector3(0.0f, 0.5f, 0.0f));

	mCompoundShape->addChildShape(localTrans, mChassisShape);

	localTrans.setOrigin(position);
	mChassisRigidBody = CreateRigidBody(mass, localTrans, mCompoundShape);
	mChassisRigidBody->setCenterOfMassTransform(localTrans);
	mChassisRigidBody->setLinearVelocity(btVector3(0, 0, 0));
	mChassisRigidBody->setAngularVelocity(btVector3(0, 0, 0));
	mDynamicsWorld->addRigidBody(mChassisRigidBody);

	mDynamicsWorld->getBroadphase()->getOverlappingPairCache()->cleanProxyFromPairs(mChassisRigidBody->getBroadphaseHandle(), mDynamicsWorld->getDispatcher());

	int rightIndex = 0;
	int upIndex = 1;
	int forwardIndex = 2;
	btVector3 wheelDirectionCS0(0, -1, 0);
	btVector3 wheelAxleCS(-1, 0, 0);
	btScalar suspensionRestLength(0.5);

	mVehicleRaycaster = new btDefaultVehicleRaycaster(mDynamicsWorld);
	mRaycastVehicle = new btRaycastVehicle(mVehicleTuning, mChassisRigidBody, mVehicleRaycaster);

	// Never deactivate the vehicle
	mChassisRigidBody->setActivationState(DISABLE_DEACTIVATION);

	mDynamicsWorld->addVehicle(mRaycastVehicle);

	float connectionHeight = 0.135f;

	m_wheelShape = new btCylinderShapeX(btVector3(mWheelWidth, mWheelRadius, mWheelRadius));

	bool isFrontWheel = true;
	//choose coordinate system
	mRaycastVehicle->setCoordinateSystem(rightIndex, upIndex, forwardIndex);

	btVector3 connectionPointCS0(mSize + (.5f*mWheelWidth), connectionHeight, 2.f*mSize - mWheelRadius);
	mRaycastVehicle->addWheel(connectionPointCS0, wheelDirectionCS0, wheelAxleCS, suspensionRestLength, mWheelRadius, mVehicleTuning, isFrontWheel);

	connectionPointCS0 = btVector3(-mSize - (.5f*mWheelWidth), connectionHeight, 2.f*mSize - mWheelRadius);
	mRaycastVehicle->addWheel(connectionPointCS0, wheelDirectionCS0, wheelAxleCS, suspensionRestLength, mWheelRadius, mVehicleTuning, isFrontWheel);

	isFrontWheel = false;
	connectionPointCS0 = btVector3(-mSize - (.5f*mWheelWidth), connectionHeight, -1.7f*mSize + mWheelRadius);
	mRaycastVehicle->addWheel(connectionPointCS0, wheelDirectionCS0, wheelAxleCS, suspensionRestLength, mWheelRadius, mVehicleTuning, isFrontWheel);

	connectionPointCS0 = btVector3(mSize + (.5f*mWheelWidth), connectionHeight, -1.7f*mSize + mWheelRadius);
	mRaycastVehicle->addWheel(connectionPointCS0, wheelDirectionCS0, wheelAxleCS, suspensionRestLength, mWheelRadius, mVehicleTuning, isFrontWheel);

	for (int i = 0; i<mRaycastVehicle->getNumWheels(); i++)
	{
		btWheelInfo& wheel = mRaycastVehicle->getWheelInfo(i);
		wheel.m_suspensionStiffness = mSuspensionStiffness;
		wheel.m_wheelsDampingRelaxation = mSuspensionDamping;
		wheel.m_wheelsDampingCompression = mSuspensionCompression;
		wheel.m_frictionSlip = mWheelFriction;
		wheel.m_rollInfluence = mRollInfluence;
	}

	return true;
}

void BasicCar::Destroy()
{
	mDynamicsWorld->removeRigidBody(mChassisRigidBody);
	delete mChassisRigidBody->getMotionState();

	mDynamicsWorld->removeVehicle(mRaycastVehicle);

	delete mChassisRigidBody;
	delete mCompoundShape;
	delete mChassisShape;
	delete m_wheelShape;
	delete mVehicleRaycaster;
	delete mRaycastVehicle;
}

void BasicCar::Update(KeyboardDevice* keyboard, GamepadDevice* gamepad, float elapsedTime)
{
	bool up_key = false;
	bool down_key = false;
	bool left_key = false;
	bool right_key = false;

	if (keyboard != 0)
	{
		//update cam
		if (keyboard->KeyDown(Key::W))
			up_key = true;
		if (keyboard->KeyDown(Key::S))
			down_key = true;
		if (keyboard->KeyDown(Key::A))
			left_key = true;
		if (keyboard->KeyDown(Key::D))
			right_key = true;
	}

	if (gamepad != 0)
	{
		//update cam
		if (gamepad->KeyDown(Gamepad::Up))
			up_key = true;
		if (gamepad->KeyDown(Gamepad::Down))
			down_key = true;
		if (gamepad->KeyDown(Gamepad::Left))
			left_key = true;
		if (gamepad->KeyDown(Gamepad::Right))
			right_key = true;
	}


	if (right_key)
	{
		mSteeringValue -= mSteeringIncrement;
		if (mSteeringValue < -mSteeringClamp)
			mSteeringValue = -mSteeringClamp;
	}
	else
	{
		// Return wheel to original position
		if (mSteeringValue <= 0.0f)
		{
			mSteeringValue += mSteeringIncrement;

			if (mSteeringValue > 0.0f)
				mSteeringValue = 0.0f;
		}
	}

	if (left_key)
	{
		mSteeringValue += mSteeringIncrement;
		if (mSteeringValue > mSteeringClamp)
			mSteeringValue = mSteeringClamp;
	}
	else
	{
		// Return wheel to original position
		if (mSteeringValue >= 0.0f)
		{
			mSteeringValue -= mSteeringIncrement;
			if (mSteeringValue < 0.0f)
				mSteeringValue = 0.0f;
		}
	}

	if (up_key)
	{
		mEngineForce = mMaxEngineForce;
		mBreakingForce = 0.f;
	}
	else
	{
		mEngineForce = 0.f;
	}

	if (down_key)
	{
		mEngineForce = -mMaxEngineForce;
		mBreakingForce = 0.f;
	}
	else
	{
		mBreakingForce = 0.f;
	}



	int wheelIndex = 2;
	mRaycastVehicle->applyEngineForce(mEngineForce, wheelIndex);
	mRaycastVehicle->setBrake(mBreakingForce, wheelIndex);
	wheelIndex = 3;
	mRaycastVehicle->applyEngineForce(mEngineForce, wheelIndex);
	mRaycastVehicle->setBrake(mBreakingForce, wheelIndex);

	wheelIndex = 0;
	mRaycastVehicle->setSteeringValue(mSteeringValue, wheelIndex);
	wheelIndex = 1;
	mRaycastVehicle->setSteeringValue(mSteeringValue, wheelIndex);

	// Update vehicle direction
	btWheelInfo& wheel = mRaycastVehicle->getWheelInfo(0);
	btVector3 up = -wheel.m_raycastInfo.m_wheelDirectionWS;
	const btVector3& right = wheel.m_raycastInfo.m_wheelAxleWS;
	mForward = up.cross(right);
	mForward.normalize();
}

void BasicCar::Render(Camera3d* cam, glm::mat4 &projection)
{
	btVector3	worldBoundsMin, worldBoundsMax;
	mDynamicsWorld->getBroadphase()->getBroadphaseAabb(worldBoundsMin, worldBoundsMax);

	//
	glm::mat4 camView = glm::lookAt(cam->Position, glm::vec3(GetWorldTransform().getOrigin()[0], GetWorldTransform().getOrigin()[1], GetWorldTransform().getOrigin()[2]), cam->Up);
	
	//draw chasis
	{
		glm::mat4 model;
		//glm::mat4 view;
		glm::mat4 mvp;

		//get box matrix from bullet object
		float cubeMatrix[16];
		btTransform trn;
		mRaycastVehicle->getRigidBody()->getMotionState()->getWorldTransform(trn);
		trn.getOpenGLMatrix((btScalar*)&cubeMatrix);

		model = btScalar2glmMat4(cubeMatrix);

		mvp = projection * camView * model;

		_shader->SetUniform(VertexShader, "mvp", mvp);

		_carModel->Draw();
	}

	//draw wheels
	for (int i = 0; i<mRaycastVehicle->getNumWheels(); i++)
	{
		//synchronize the wheels with the (interpolated) chassis worldtransform
		mRaycastVehicle->updateWheelTransform(i, true);

		float cubeMatrix[16];
		mRaycastVehicle->getWheelInfo(i).m_worldTransform.getOpenGLMatrix((btScalar*)&cubeMatrix);

		glm::mat4 model;
		glm::mat4 mvp;

		model = btScalar2glmMat4(cubeMatrix);

		mvp = projection * camView * model;

		_shader->SetUniform(VertexShader, "mvp", mvp);

		_wheelModel->Draw();
	}
}

btRigidBody*  BasicCar::CreateRigidBody(float mass, const btTransform& startTransform, btCollisionShape* shape)
{
	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = (mass != 0.f);

	btVector3 localInertia(0, 0, 0);
	if (isDynamic)
		shape->calculateLocalInertia(mass, localInertia);

	//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo cInfo(mass, myMotionState, shape, localInertia);
	btRigidBody* body = new btRigidBody(cInfo);

	return body;
}

glm::mat4 BasicCar::btScalar2glmMat4(btScalar* matrix)
{
	return glm::mat4(
		matrix[0], matrix[1], matrix[2], matrix[3],
		matrix[4], matrix[5], matrix[6], matrix[7],
		matrix[8], matrix[9], matrix[10], matrix[11],
		matrix[12], matrix[13], matrix[14], matrix[15]);
}