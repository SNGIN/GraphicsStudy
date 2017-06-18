#pragma once
#include "ShapeObject.h"

class CubeObject :public ShapeObject
{
	public:
		CubeObject();
		CubeObject(Vector3 scale);
		~CubeObject();
};

