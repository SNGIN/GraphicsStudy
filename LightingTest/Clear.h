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
	//クリア画面のイメージ

	int mCount;
};