#pragma once
#include "StaticObj.h"
#include "ShapeObject.h"
#include "CubeObject.h"
#include "State.h"
#include "Rect.h"

class Ground:public StaticObj
{
private:
	Rect* m_Rect;
	CubeObject* m_Cube;
public:
	Ground(){}
	~Ground();
	Ground(GLfloat width, GLfloat height,Physics* physics);

	float xRotate;
	float yRotate;
	float zRotate;

	GLfloat Matrix_rot[16];

	StaticObj* Draw();
	StaticObj* Update();
};

