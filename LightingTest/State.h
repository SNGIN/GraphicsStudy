#pragma once
#include "Commonheader.h"
#include "GoalObj.h"

class StaticObj;
class DynamicObj;

//�Q�[���̏�Ԃ��Ǘ�����N���X
class State
{
public:
	State(int stageID);
	~State();

	void Update();
	void Draw()const;
	//�O����n�������
	bool hasCleared()const;
private:
	StaticObj* mStaticObjects;
	DynamicObj* mDynamicObjects;
	int mStaticObjectNumber;
	int mDynamicObjectNumber;
	int mstageID;

	GoalObj* mGoalObj;
};

