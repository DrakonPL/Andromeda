#ifndef BasicCar_H
#define BasicCar_H

#include "bullet/BulletDynamics/Vehicle/btRaycastVehicle.h"
#include "bullet/LinearMath/btVector3.h"
#include "bullet/LinearMath/btMatrix3x3.h"
#include "bullet/LinearMath/btTransform.h"
#include "bullet/LinearMath/btQuickprof.h"
#include "bullet/LinearMath/btAlignedObjectArray.h"
#include "bullet/btBulletDynamicsCommon.h"

#include <Andromeda/Graphics/Models/ModelObj.h>
#include <Andromeda/Graphics/Shader.h>
#include <Andromeda/Graphics/Camera3d.h>

#include <Andromeda/Input/InputManager.h>

using namespace Andromeda::Graphics;
using namespace Andromeda::Input;

class BasicCar
{
private:

	// Shaders
	Shader* _shader;

	//model
	ModelObj* _carModel;
	ModelObj* _wheelModel;

	//bullet stuff
	btRigidBody*		mChassisRigidBody;
	btCompoundShape*	mCompoundShape;
	btCollisionShape*	mChassisShape;

	btCollisionShape* m_wheelShape;

	btRaycastVehicle::btVehicleTuning	mVehicleTuning;
	btVehicleRaycaster*					mVehicleRaycaster;
	btRaycastVehicle*					mRaycastVehicle;

	btDynamicsWorld*					mDynamicsWorld;

	// Stores vehicle direction
	btVector3	mForward;

	// variables for motion
	float	mSteeringValue;
	float	mMaxEngineForce;//this should be engine/velocity dependent
	float	mMaxBreakingForce;
	float	mSteeringIncrement;
	float	mSteeringClamp;
	float	mEngineForce;
	float	mBreakingForce;

	// car characteristics
	float	mWheelRadius;
	float	mSuspensionStiffness;
	float	mSuspensionDamping;
	float	mSuspensionCompression;
	float	mWheelFriction;
	float	mRollInfluence;
	float	mWheelWidth;

	float	mSize;

	btRigidBody* CreateRigidBody(float mass, const btTransform& startTransform, btCollisionShape* shape);
	glm::mat4 btScalar2glmMat4(btScalar* matrix);

public:

	BasicCar();
	~BasicCar();

	bool Create(ModelObj* chasis, ModelObj* wheel,Shader* shader,btDynamicsWorld *dynamicsWorld, btVector3 &position, btScalar mass);
	void Destroy();

	void Update(KeyboardDevice* keyboard, GamepadDevice* gamepad, float elapsedTime);
	void Render(glm::mat4 &camView, glm::mat4 &projection);

	btScalar GetSpeed() { return mRaycastVehicle->getCurrentSpeedKmHour(); }
	btScalar GetSteeringValue() { return mSteeringValue; }
	btVector3 GetDirection() { return mForward; }
	btTransform &GetWorldTransform() { return mRaycastVehicle->getRigidBody()->getWorldTransform(); }
};


#endif