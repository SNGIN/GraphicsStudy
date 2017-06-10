#include "DynamicObj.h"


DynamicObj::DynamicObj()
{
}


DynamicObj::~DynamicObj()
{
}

void DynamicObj::Set(GLfloat x, GLfloat y,GLfloat z){
	physics->SetRigidBodyPos(rigidBodyIndex, Vector3(x, y, z));
}

vector3 DynamicObj::GetPos(){
	return vector3(States(rigidBodyIndex).m_position.getX(), 
		States(rigidBodyIndex).m_position.getY(),
		States(rigidBodyIndex).m_position.getZ());
}