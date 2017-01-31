#pragma once
#include "GameSeaquence.h"


class Pause:public GameSeaquence
{
public:
	Pause();
	~Pause();
	Boot* Update(GameSeaquenceController*);
};

