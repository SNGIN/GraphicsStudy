#pragma once
#include "Model.h"
#include "DynamicObj.h"
#include "SphereObject.h"

class Player:public DynamicObj
{
private:
	Model* m_bunny;
	SphereObject* m_sphere;

	GLfloat speed = 0.025;
public:
	Player();
	~Player();
	DynamicObj* Draw();
	DynamicObj* Update();
};

