#include "DynamicObj.h"


DynamicObj::DynamicObj()
{
}


DynamicObj::~DynamicObj()
{
}

void DynamicObj::Set(GLfloat x, GLfloat y){
	position.set(x, 0, y);
}