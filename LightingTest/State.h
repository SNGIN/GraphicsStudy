#pragma once
#include "Commonheader.h"
#include "GoalObj.h"
#include "GameSeaquenceController.h"
#include "Physics.h"

class StaticObj;
class DynamicObj;

//ゲームの状態を管理するクラス
class State
{
public:
	State(){}
	State(int stageID);
	~State();

	void PhysicsUpdate();
	void Update();
	void Draw();
	//外から渡される情報
	bool hasCleared()const;
	bool hasMissed()const;

	Physics* GetPhysics();

private:
	StaticObj** mStaticObjects;
	DynamicObj** mDynamicObjects;
	int mStaticObjectNumber;
	int mDynamicObjectNumber;
	int mstageID;

	//check用変数
	bool clear = false;
	bool miss = false;

	Physics* m_Physics;
};

