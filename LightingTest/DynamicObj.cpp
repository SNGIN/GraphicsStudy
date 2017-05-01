#include "DynamicObj.h"


DynamicObj::DynamicObj()
{
}


DynamicObj::~DynamicObj()
{
}

void DynamicObj::Set(GLfloat x, GLfloat y){
	position.set(x, 0.5, y);
}

vector3 DynamicObj::Get(){
	return position;
}