#pragma once
#include "Model.h"
#include "DynamicObj.h"

class Player:public DynamicObj
{
private:
	Model* m_bunny;
	GLfloat speed = 0.025;
public:
	Player();
	~Player();
	DynamicObj* Draw();
	DynamicObj* Update();
};

