#pragma once
#include "Seaquence.h"
#include "Commonheader.h"

class SeaquenceController;

//�^�C�g���̋������`����
class Title:public Seaquence
{
public:
	Title();
	~Title();

	Boot* Update(SeaquenceController*);
private:
	//�^�C�g����ʂ̃C���[�W�ێ�
};