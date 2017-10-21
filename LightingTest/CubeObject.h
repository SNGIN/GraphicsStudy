#pragma once
#include "ShapeObject.h"
#include "Physics.h"

class CubeObject :public ShapeObject
{
	public:
		CubeObject();
		CubeObject(Vector3 scale,
			char* vert, char* flag,
			GLfloat* ambColor, GLfloat* diffColor, GLfloat *specColor, GLfloat shiness);
		~CubeObject();
};

