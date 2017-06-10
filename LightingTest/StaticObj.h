#pragma once
#include "Commonheader.h"
#include "PhysicsInclude.h"
#include "Physics.h"

//静的オブジェクトを管理するクラス
class StaticObj
{
public:
	StaticObj();
	~StaticObj();
	enum ObjFlag
	{
		FLAG_WALL = (1 << 0),
		FLAG_GOAL = (1 << 1),
	};
	bool CheckFlag(unsigned)const;
	void SetFlag(unsigned);
	void ResetFlag(unsigned);

	void Set(GLfloat x, GLfloat y);

	RigidbodyState States(int index){
		return physics->GetRigidBodyState(index);
	}
	RigidBodyElements Bodies(int index){
		return physics->GetRigidBodyElements(index);
	}
	Collider Collider(int index){
		return physics->GetCollider(index);
	}
	int GetRigidbodyIndex(){
		return rigidBodyIndex;
	}

	virtual StaticObj* Draw(){ return 0; };
	virtual StaticObj* Update(){ return 0; };
private:
	unsigned mFlags;

protected:
	vector3 position;
	//物理データ関連のIndex
	int rigidBodyIndex;
	Physics* physics;

};

