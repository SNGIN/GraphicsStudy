#pragma once
#include "GameSeaquence.h"

class GameSeaquenceController;

class Clear:public GameSeaquence
{
public:
	Clear();
	~Clear();
	Boot* Update(GameSeaquenceController*);
private:
	//�N���A��ʂ̃C���[�W

	int mCount;
};