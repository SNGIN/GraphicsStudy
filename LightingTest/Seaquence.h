#pragma once
#include "Boot.h"
class SeaquenceController;

//各シーケンスを定義するクラス
class Seaquence : public Boot
{
public:
	virtual ~Seaquence();
	Boot* Update(Boot*);
	virtual Boot* Update(SeaquenceController*) = 0;
};

