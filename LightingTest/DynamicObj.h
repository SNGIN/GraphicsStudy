#pragma once
#include "Commonheader.h"
#include "PhysicsInclude.h"
#include "Physics.h"

//動くオブジェクトの挙動を定義するクラス
class DynamicObj
{
protected:
	vector3 position;
	Physics* physics;
	//物理データ関連のIndex
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

