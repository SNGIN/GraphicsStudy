#include "Ending.h"
#include "Commonheader.h"
#include "Title.h"

Ending::Ending()
{

	std::cout << "Ending" << std::endl;
}


Ending::~Ending()
{
	//�C���[�W���\�[�X�̉��
	//Common::Delete();
}

Boot* Ending::Update(SeaquenceController*){
	Boot* next = this;
	if (mCount == 120){
		next = new Title;
	}
	//�`��

	++mCount;
	return next;
}
