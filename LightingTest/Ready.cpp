#include "Ready.h"
#include "GameSeaquenceController.h"
#include "Play.h"
#include "Commonheader.h"

Ready::Ready() :mCount(0), mStarted(false)
{
	//�C���[�W������ďo��
}


Ready::~Ready()
{
	//�C���[�W���\�[�X�̔j��
}

Boot* Ready::Update(GameSeaquenceController* controller){
	Boot* next = this;
	if (!mStarted){
		controller->StartLoading();
		mStarted = true;
	}

	if (mCount >= 120){
		next = new Play;
	}
	else if (mCount >= 60){
		//�S�[
		std::cout << "Go" << std::endl;
	}
	else{
		//���f�B
		std::cout << "Ready" << std::endl;
	}
	//�`��
	controller->DrawState();
	++mCount;
	return next;
}
