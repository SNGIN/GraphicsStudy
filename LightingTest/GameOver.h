#pragma once
#include "Seaquence.h"

class GameOver:public Seaquence
{
public:
	GameOver();
	~GameOver();
	Boot* Update(SeaquenceController*);
private:
	//ゲームオーバーイメージのリソース

	int mCount;
};