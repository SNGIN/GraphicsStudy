#include "Ending.h"
#include "Commonheader.h"
#include "Title.h"

Ending::Ending()
{
}


Ending::~Ending()
{
	//�C���[�W���\�[�X�̉��
	//Common::Delete();
}

Boot* Ending::Update(SeaquenceController*){
	Boot* next = this;
	if (mCount == 120){
		//next = new Title;
	}
	//�`��

	std::cout << "Ending" << std::endl;

	++mCount;
	return next;
}
