#pragma once
#include "GameSeaquence.h"

class Failure:public GameSeaquence
{
public:
	Failure();
	~Failure();
	Boot* Update(GameSeaquenceController*);
private:
	int mCount;
};

