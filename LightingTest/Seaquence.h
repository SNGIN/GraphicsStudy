#pragma once
#include "Boot.h"
class SeaquenceController;

//�e�V�[�P���X���`����N���X
class Seaquence : public Boot
{
public:
	virtual ~Seaquence();
	Boot* Update(Boot*);
	virtual Boot* Update(SeaquenceController*) = 0;
};

