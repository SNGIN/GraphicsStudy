#pragma once
#include "Commonheader.h"
#include "PhysicsInclude.h"
#include "Physics.h"

//�����I�u�W�F�N�g�̋������`����N���X
class DynamicObj
{
protected:
	vector3 position;
	Physics* physics;
	//�����f�[�^�֘A��Index
	int rigidBodyIndex;
public:
	DynamicObj();
	~DynamicObj();

	vector3 GetPos();
	RigidbodyState States(int index){
		return physics->GetRigidBodyState(index);
	}
	RigidBodyElements Bodies(int index){
		return physics->GetRigidBodyElements(index);
	}
	Collider Collider(int index){
		return physics->GetCollider(index);
	}

	bool miss;

	void Set(GLfloat x, GLfloat y,GLfloat z);
	virtual DynamicObj* Draw(){ return 0; };
	virtual DynamicObj* Update(){ return 0; };
};

