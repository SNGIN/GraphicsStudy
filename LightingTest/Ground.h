#pragma once
#include "StaticObj.h"
#include "ShapeObject.h"
#include "Rect.h"

class Ground:public StaticObj
{
private:
	Rect* m_Rect;
public:
	Ground(){}
	~Ground();
	Ground(GLfloat width, GLfloat height);

	StaticObj* Draw();
	StaticObj* Update();
};

