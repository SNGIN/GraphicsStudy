#pragma once
#include "Seaquence.h"

class GameOver:public Seaquence
{
public:
	GameOver();
	~GameOver();
	Boot* Update(SeaquenceController*);
private:
	//�Q�[���I�[�o�[�C���[�W�̃��\�[�X

	int mCount;
};