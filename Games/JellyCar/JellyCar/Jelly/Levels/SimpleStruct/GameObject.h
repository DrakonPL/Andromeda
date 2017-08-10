#ifndef GameObject_H
#define GameObject_H

typedef struct GameObject
{
	char name[64];
	float posX;
	float posY;
	float angle;
	float scaleX;
	float scaleY;
	int material;

	bool isPlatform;
	bool isMotor;

	//platform motion
	float platformOffsetX;
	float platformOffsetY;
	float platformSecondsPerLoop;
	float platformStartOffset;

	//motor
	float motorRadiansPerSecond;
};

#endif
