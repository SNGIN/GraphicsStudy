#pragma once
#include "Seaquence.h"
#include "Commonheader.h"
#include "Rect.h"

class SeaquenceController;

//�^�C�g���̋������`����
class Title:public Seaquence
{
public:
	Title();
	~Title();

	Boot* Update(SeaquenceController*);
private:
	Rect* mrect;//�^�C�g���\���Ɏg��Rect�I�u�W�F�g
};