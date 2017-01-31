#pragma once
#include "Boot.h"

class GameSeaquenceController;

class GameSeaquence:public Boot
{
public:
	~GameSeaquence();
	Boot* Update(Boot*);
	virtual Boot* Update(GameSeaquenceController*)=0;
};

