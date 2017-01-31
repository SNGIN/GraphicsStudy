#pragma once
#include "Commonheader.h"
#include "GoalObj.h"

class StaticObj;
class DynamicObj;

//ゲームの状態を管理するクラス
class State
{
public:
	State(int stageID);
	~State();

	void Update();
	void Draw()const;
	//外から渡される情報
	bool hasCleared()const;
private:
	StaticObj* mStaticObjects;
	DynamicObj* mDynamicObjects;
	int mStaticObjectNumber;
	int mDynamicObjectNumber;
	int mstageID;

	GoalObj* mGoalObj;
};

