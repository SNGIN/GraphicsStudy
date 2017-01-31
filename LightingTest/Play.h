#pragma once
#include "GameSeaquence.h"

class GameSeaquenceController;

class Play:public GameSeaquence
{
public:
	Play();
	~Play();
	Boot* Update(GameSeaquenceController*);
};

