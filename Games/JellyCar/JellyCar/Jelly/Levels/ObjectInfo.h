#ifndef ObjectInfo_H
#define ObjectInfo_H

class ObjectInfo
{
public:

	std::string name;
	float posX, posY, angle, scaleX, scaleY, material;

	ObjectInfo()
	{
		posX = posY = angle = scaleX = scaleY = material = 0.0f;
	}
};

#endif