#include "Car.h"
#include "tinyxml.h"

#include <Andromeda/FileSystem/FileManager.h>
using namespace Andromeda;

Car::Car(std::string xmlFile, World *mWorld, const Vector2& pos, int chassisMat, int tireMat)
{
	mainWorld = mWorld;

	mShapeD = 0;
	mShapeDelta = 0;
	mTransformSpeed = 1.0f;

	TransformStatus = Car::Normal;

	//loac car file
	FileSystem::BaseFile* file = FileSystem::FileManager::Instance()->GetFile(xmlFile);

	if (file == 0)
		return;

	file->Open(FileSystem::Read, FileSystem::Binary);

	int dataSize = 0;
	unsigned char* _buffer = file->GetData(dataSize);

	file->Close();
	delete file;


	//load object
	TiXmlDocument doc;
	if (!doc.LoadContent(_buffer, dataSize))
	{
		//Error - Can't load file :/
		return;
	}

	TiXmlHandle hDoc(&doc);
	TiXmlElement* pElem;
	TiXmlHandle hRoot(0);

	pElem = hDoc.FirstChildElement().Element();

	// should always have a valid root but handle gracefully if it does
	if (!pElem)
	{
		//Error - Can't find root :/
		return;
	}

	hRoot = TiXmlHandle(pElem);

	//shape A
	ClosedShape shapeA;// = new ClosedShape();
	shapeA.begin();

	TiXmlElement* PointNode = hRoot.FirstChild("Shape1").FirstChild().Element();
	for (PointNode; PointNode; PointNode = PointNode->NextSiblingElement())
	{
		float x = 0.0f, y = 0.0f;
		x = atof(PointNode->Attribute("x"));
		y = atof(PointNode->Attribute("y"));
		shapeA.addVertex(Vector2(x, y));
	}

	shapeA.finish(true);


	//shape B
	ClosedShape shapeB;// = new ClosedShape();
	shapeB.begin();

	TiXmlElement* PointNode2 = hRoot.FirstChild("Shape2").FirstChild().Element();
	for (PointNode2; PointNode2; PointNode2 = PointNode2->NextSiblingElement())
	{
		float x = 0.0f, y = 0.0f;
		x = atof(PointNode2->Attribute("x"));
		y = atof(PointNode2->Attribute("y"));
		shapeB.addVertex(Vector2(x, y));
	}

	shapeB.finish(true);

	//create chassis
	float massPerPoint = 1.0f;
	float shapeK = 100.0f;
	float shapeDamp = 10.0f;
	float edgeK = 100.0f;
	float edgeDamp = 10.0f;

	pElem = hRoot.FirstChild("Chassis").Element();
	if (pElem != NULL)
	{
		massPerPoint = atof(pElem->Attribute("MassPerPoint"));
		shapeK = atof(pElem->Attribute("ShapeK"));
		shapeDamp = atof(pElem->Attribute("ShapeDamp"));
		edgeK = atof(pElem->Attribute("EdgeK"));
		edgeDamp = atof(pElem->Attribute("EdgeDamp"));

	}
	else
	{
		return;
	}

	mChassis = new Chassis(mWorld, shapeA, shapeB, massPerPoint, shapeK, shapeDamp, edgeK, edgeDamp, pos, Vector2::One);
	mChassis->setMaterial(chassisMat);


	// now add internal springs to the chassis
	TiXmlElement* SpingNode = hRoot.FirstChild("InternalSprings").FirstChild().Element();
	for (SpingNode; SpingNode; SpingNode = SpingNode->NextSiblingElement())
	{
		int pt1, pt2;
		float k, damp;
		pt1 = atoi(SpingNode->Attribute("ptA"));
		pt2 = atoi(SpingNode->Attribute("ptB"));
		k = atof(SpingNode->Attribute("springK"));
		damp = atof(SpingNode->Attribute("springDamp"));

		mChassis->addInternalSpring(pt1, pt2, k, damp);
	}

	//add polygons to chassis
	mChassis->StartPolys();

	TiXmlElement* PolygonNode = hRoot.FirstChild("Polygons").FirstChild().Element();
	for (PolygonNode; PolygonNode; PolygonNode = PolygonNode->NextSiblingElement())
	{
		int pt1 = 0, pt2 = 0, pt3 = 0;
		pt1 = atoi(PolygonNode->Attribute("pt1"));
		pt2 = atoi(PolygonNode->Attribute("pt2"));
		pt3 = atoi(PolygonNode->Attribute("pt3"));

		mChassis->AddPoly(pt1, pt2, pt3);
	}

	mChassis->EndPolys();

	//clean tire collection
	mTires.clear();

	//now build tires...
	int counter = 0;
	TiXmlElement* TireNode = hRoot.FirstChild("Tire").Element();
	for (TireNode; TireNode; TireNode = TireNode->NextSiblingElement())
	{
		if (counter < 2)
		{
			int segments = 12;
			float tire_rad = 1.0f;
			Vector2 tire_offset(0, 0);
			float tire_mass_per_point = 1.0f;
			float pressure1 = 50.0f;
			float pressure2 = 200.0f;
			shapeK = 100.0f;
			shapeDamp = 10.0f;
			float edgeK1 = 100.0f;
			float edgeDamp1 = 10.0f;
			float edgeK2 = 100.0f;
			float edgeDamp2 = 10.0f;
			float drive = 1.0f;
			float t1 = 10.0f;
			float t2 = 10.0f;
			float maxO1 = 10.0f;
			float maxO2 = 10.0f;

			//load
			drive = atof(TireNode->Attribute("Drive"));
			tire_offset.X = atof(TireNode->Attribute("PosX"));
			tire_offset.Y = atof(TireNode->Attribute("PosY"));
			segments = atoi(TireNode->Attribute("Segments"));
			tire_rad = atof(TireNode->Attribute("Radius"));
			tire_mass_per_point = atof(TireNode->Attribute("MassPerPoint"));
			pressure1 = atof(TireNode->Attribute("Pressure1"));
			pressure2 = atof(TireNode->Attribute("Pressure2"));
			shapeK = atof(TireNode->Attribute("ShapeK"));
			shapeDamp = atof(TireNode->Attribute("ShapeDamp"));
			edgeK1 = atof(TireNode->Attribute("EdgeK1"));
			edgeDamp1 = atof(TireNode->Attribute("EdgeDamp1"));
			edgeK2 = atof(TireNode->Attribute("EdgeK2"));
			edgeDamp2 = atof(TireNode->Attribute("EdgeDamp2"));
			t1 = atof(TireNode->Attribute("Torque1"));
			t2 = atof(TireNode->Attribute("Torque2"));
			maxO1 = atof(TireNode->Attribute("MaxOmega1"));
			maxO2 = atof(TireNode->Attribute("MaxOmega2"));


			ClosedShape fws;//= new ClosedShape();
							//setTexturePoints(std::vector<Vector2>	mPoints)
			fws.begin();
			for (int i = 0; i < 360; i += segments)
			{
				fws.addVertex(Vector2(cos(VectorTools::degToRad((float)-i)) * tire_rad, sin(VectorTools::degToRad((float)-i))* tire_rad));
			}
			fws.finish();

			Tire *t = new Tire(mWorld, fws, drive, tire_mass_per_point, pressure1, pressure2, shapeK, shapeDamp, edgeK1, edgeDamp1, edgeK2, edgeDamp2, t1, t2, maxO1, maxO2, pos + tire_offset);
			t->setMaterial(tireMat);
			//t->setTexturePoints();
			mTires.push_back(t);


			TiXmlElement* TireElements = TireNode->FirstChildElement();
			for (TireElements; TireElements; TireElements = TireElements->NextSiblingElement())
			{

				int pm = atoi(TireElements->Attribute("PointMassID"));
				float shockD1 = atof(TireElements->Attribute("SpringD1"));
				float shockD2 = atof(TireElements->Attribute("SpringD2"));
				float shockK1 = atof(TireElements->Attribute("SpringK1"));
				float shockK2 = atof(TireElements->Attribute("SpringK2"));
				float shockDamp1 = atof(TireElements->Attribute("SpringDamp1"));
				float shockDamp2 = atof(TireElements->Attribute("SpringDamp2"));

				mChassis->AddShock(pm, t, shockD1, shockD2, shockK1, shockK2, shockDamp1, shockDamp2);

			}
			counter++;
		}

	}

	ballonShape.begin();
	ballonShape.addVertex(Vector2(0, 1));
	ballonShape.addVertex(Vector2(0.309017, 0.9510565));
	ballonShape.addVertex(Vector2(0.5877852, 0.809017));
	ballonShape.addVertex(Vector2(0.809017, 0.5877852));
	ballonShape.addVertex(Vector2(0.9510565, 0.309017));
	ballonShape.addVertex(Vector2(1, 1.216796E-08));
	ballonShape.addVertex(Vector2(0.9510565, -0.309017));
	ballonShape.addVertex(Vector2(0.809017, -0.5877852));
	ballonShape.addVertex(Vector2(0.5877852, -0.809017));
	ballonShape.addVertex(Vector2(0.309017, -0.9510565));
	ballonShape.addVertex(Vector2(0.03797042, -0.9984476));
	ballonShape.addVertex(Vector2(0.03687066, -1.33094));
	ballonShape.addVertex(Vector2(-0.03791077, -1.330736));
	ballonShape.addVertex(Vector2(-0.03825687, -0.9984476));
	ballonShape.addVertex(Vector2(-0.309017, -0.9510565));
	ballonShape.addVertex(Vector2(-0.5877852, -0.809017));
	ballonShape.addVertex(Vector2(-0.809017, -0.5877853));
	ballonShape.addVertex(Vector2(-0.9510565, -0.309017));
	ballonShape.addVertex(Vector2(-1, -3.65039E-08));
	ballonShape.addVertex(Vector2(-0.9510565, 0.3090169));
	ballonShape.addVertex(Vector2(-0.809017, 0.5877852));
	ballonShape.addVertex(Vector2(-0.5877853, 0.8090169));
	ballonShape.addVertex(Vector2(-0.309017, 0.9510565));
	ballonShape.finish();

	ballon = false;
}

Car::~Car()
{
	while (!mTires.empty())
	{
		Tire* t = mTires.back();
		mainWorld->removeBody(t);
		delete t;
		mTires.pop_back();
	}

	mainWorld->removeBody(mChassis);
	delete mChassis;
}

void Car::clearForces()
{
	for (int i = 0; i < mTires.size(); i++)
		mTires[i]->SetShockForce(Vector2::Zero);

	if (ballon)
		mChassis->SetShockForce(Vector2::Zero);
}

void Car::setTorque(float t)
{
	for (int i = 0; i < mTires.size(); i++)
		mTires[i]->SetTorque(t * mTires[i]->GetDrive());

	if (ballon)
	{
		ballonBody->SetTorque(t);
	}
}

bool Car::Transform()
{
	if (mShapeD == 0.0f)
	{
		// we are currently small.  transform to BIG.
		mShapeDelta = mTransformSpeed;
		return true;
	}
	else if (mShapeD == 1.0f)
	{
		// we are currently BIG, transform to small.
		mShapeDelta = -mTransformSpeed;
		return true;
	}

	return false;
}

void Car::update(float elapsed)
{
	if (mShapeDelta != 0.0f)
	{
		mShapeD += (mShapeDelta * elapsed);
		if (mShapeD > 0.0f)
		{
			mChassis->smallBig = true;
			mTires[0]->smallBig = true;
			mTires[1]->smallBig = true;
		}
		else
		{
			mChassis->smallBig = false;
			mTires[0]->smallBig = false;
			mTires[1]->smallBig = false;
		}
		if (mShapeD > 1.0f) { mShapeDelta = 0.0f; mShapeD = 1.0f; TransformStatus = Transformed; }
		if (mShapeD < 0.0f) { mShapeDelta = 0.0f; mShapeD = 0.0f; TransformStatus = Normal; }

		mChassis->InterpolateShape(mShapeD);
		for (int i = 0; i < mTires.size(); i++)
			mTires[i]->InterpolatePressure(mShapeD);
	}

	if (ballon)
		ballonBody->SetBallonPosition(mChassis->getPointMass(5)->Position, mChassis->getDerivedVelocity());
}

void Car::SetChassisTextures(Texture* small, Texture* big)
{
	smallChassisTexture = small;
	bigChassisTexture = big;
}

void Car::SetTireTextures(Texture* small, Texture* big)
{
	smallTireTexture = small;
	bigTireTexture = big;
}

void Car::Draw(glm::mat4 &proj)
{
	if (!mChassis->smallBig)
	{
		mChassis->Draw(proj, smallChassisTexture);
	}
	else
	{
		mChassis->Draw(proj, bigChassisTexture);
	}	

	for (int i = 0; i < mTires.size(); i++)
	{
		if (!mChassis->smallBig)
		{
			mTires[i]->Draw(proj, smallTireTexture);
		}
		else
		{
			mTires[i]->Draw(proj, bigTireTexture);
		}		
	}		

	if (ballon)
	{
		ballonBody->Draw(proj);
	}
}

void Car::UseNearestGracity(bool state)
{
	mChassis->UseNearestGracity(state);

	for (int i = 0; i < mTires.size(); i++)
	{
		mTires[i]->UseNearestGracity(state);
	}
}

void Car::UseBallon(bool state)
{
	if (ballon != state)
	{
		if (state == true)
		{
			activateBallon();
			ballonBody->SetBallonState(true);
			ballonBody->SetBallonBody(mChassis);			
			
			mChassis->SetBallonState(true);
		}
		else
		{
			ballonBody->SetBallonState(false);

			mChassis->SetBallonState(false);

			deactivateBallon();
		}

		ballon = state;
	}
}

void Car::activateBallon()
{
	if (ballon == false)
	{
		AABB chassisAabb = mChassis->getAABB();
		Vector2 ballPosition(chassisAabb.getCenter().X, chassisAabb.Max.Y + 1);

		ballonBody = new GameBallonBody(mainWorld, ballonShape, 1.0f, 300.0f, 15.0f, 300.0f, 15.0f, ballPosition, 0.0f, Vector2(1, 1), false);
		ballonBody->setMaterial(3);

		ballonBody->addInternalSpring(22, 1, 100, 10);
		ballonBody->addInternalSpring(2, 21, 100, 10);
		ballonBody->addInternalSpring(20, 3, 100, 10);
		ballonBody->addInternalSpring(4, 19, 100, 10);
		ballonBody->addInternalSpring(18, 5, 100, 10);
		ballonBody->addInternalSpring(6, 17, 100, 10);
		ballonBody->addInternalSpring(16, 7, 100, 10);
		ballonBody->addInternalSpring(8, 15, 100, 10);
		ballonBody->addInternalSpring(14, 9, 100, 10);
		ballonBody->addInternalSpring(10, 13, 100, 10);
		ballonBody->addInternalSpring(0, 10, 100, 10);
		ballonBody->addInternalSpring(0, 13, 100, 10);
		ballonBody->addInternalSpring(13, 11, 100, 10);
		ballonBody->addInternalSpring(12, 10, 100, 10);
		ballonBody->addInternalSpring(22, 9, 100, 10);
		ballonBody->addInternalSpring(14, 1, 100, 10);
		ballonBody->addInternalSpring(21, 8, 100, 10);
		ballonBody->addInternalSpring(15, 2, 100, 10);
		ballonBody->addInternalSpring(3, 16, 100, 10);
		ballonBody->addInternalSpring(17, 4, 100, 10);
		ballonBody->addInternalSpring(6, 19, 100, 10);
		ballonBody->addInternalSpring(20, 7, 100, 10);

		ballonBody->AddTriangle(22, 0, 10);
		ballonBody->AddTriangle(13, 10, 22);
		ballonBody->AddTriangle(22, 21, 13);
		ballonBody->AddTriangle(13, 20, 21);
		ballonBody->AddTriangle(20, 19, 13);
		ballonBody->AddTriangle(13, 19, 18);
		ballonBody->AddTriangle(18, 17, 13);
		ballonBody->AddTriangle(13, 14, 17);
		ballonBody->AddTriangle(17, 16, 14);
		ballonBody->AddTriangle(14, 15, 16);
		ballonBody->AddTriangle(0, 1, 10);
		ballonBody->AddTriangle(10, 9, 1);
		ballonBody->AddTriangle(9, 2, 1);
		ballonBody->AddTriangle(2, 3, 9);
		ballonBody->AddTriangle(9, 8, 3);
		ballonBody->AddTriangle(3, 4, 8);
		ballonBody->AddTriangle(8, 7, 4);
		ballonBody->AddTriangle(4, 5, 7);
		ballonBody->AddTriangle(7, 6, 5);
		ballonBody->AddTriangle(13, 10, 12);
		ballonBody->AddTriangle(12, 11, 10);
		ballonBody->FinalizeTriangles();
	}
}

void Car::deactivateBallon()
{
	if (ballon)
	{
		mainWorld->removeBody(ballonBody);
		delete ballonBody;
	}
}

Vector2 Car::getPosition() { return mChassis->getDerivedPosition(); }
Vector2 Car::getVelocity() { return mChassis->getDerivedVelocity(); }
float Car::getTireOmega(int index) { return mTires[index]->getDerivedOmega(); }

Body* Car::getChassisBody() { return mChassis; }

int Car::getTireCount() { return mTires.size(); }
Tire* Car::getTire(int index) { return mTires[index]; }

void Car::setChassisTorque(float t) { mChassis->SetTorque(t); }