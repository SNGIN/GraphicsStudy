#pragma once
#include "Seaquence.h"

class Ending:public Seaquence
{
public:
	Ending();
	~Ending();
	Boot* Update(SeaquenceController*);
private:
	//エンディングイメージ
	int mCount;
};