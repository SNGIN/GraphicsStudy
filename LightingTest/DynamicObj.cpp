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
	return vector3(physics->GetRigidBodyState(rigidBodyIndex).m_position.getX(), 
		physics->GetRigidBodyState(rigidBodyIndex).m_position.getY(), 
		physics->GetRigidBodyState(rigidBodyIndex).m_position.getZ());
}