#pragma once
#include "GameSeaquence.h"

class GameSeaquenceController;


class Ready:public GameSeaquence
{
public:
	Ready();
	~Ready();
	Boot* Update(GameSeaquenceController*);
private:
	int mCount;
	bool mStarted;
};