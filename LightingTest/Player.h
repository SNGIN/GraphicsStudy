#pragma once
#include "Model.h"
#include "DynamicObj.h"
#include "SphereObject.h"
#include "State.h"

class Player:public DynamicObj
{
private:
	Model* m_bunny;
	SphereObject* m_sphere;
	GameSeaquenceController* m_gameController;

	GLfloat speed = 0.025;
public:
	Player(){};
	Player(Physics* mPhysics);
	~Player();
	DynamicObj* Draw();
	DynamicObj* Update();
};

