#pragma once
#include "Seaquence.h"

class Ending:public Seaquence
{
public:
	Ending();
	~Ending();
	Boot* Update(SeaquenceController*);
private:
	//�G���f�B���O�C���[�W
	int mCount;
};