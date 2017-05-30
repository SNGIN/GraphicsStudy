#pragma once
#include "Commonheader.h"
#include "GoalObj.h"
#include "GameSeaquenceController.h"
#include "Physics.h"

class StaticObj;
class DynamicObj;

//�Q�[���̏�Ԃ��Ǘ�����N���X
class State
{
public:
	State(){}
	State(int stageID);
	~State();

	void PhysicsUpdate();
	void Update();
	void Draw();
	//�O����n�������
	bool hasCleared()const;
	bool hasMissed()const;

	Physics* GetPhysics();

private:
	StaticObj** mStaticObjects;
	DynamicObj** mDynamicObjects;
	int mStaticObjectNumber;
	int mDynamicObjectNumber;
	int mstageID;

	//check�p�ϐ�
	bool clear = false;
	bool miss = false;

	Physics* m_Physics;
};

