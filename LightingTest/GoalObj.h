#pragma once
#include "StaticObj.h"
class GoalObj :
	public StaticObj
{
public:
	GoalObj();
	~GoalObj();

	bool CheckGoal();

private:
	bool mGoalFlag = false;
};

