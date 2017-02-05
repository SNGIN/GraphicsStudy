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
		//���f�B
		std::cout << "Ready" << std::endl;
	}

	if (mCount >= 120){
		//�S�[
		std::cout << "Go" << std::endl;
		next = new Play;
	}
	else if (mCount >= 60){
	}
	else{

	}
	//�`��
	controller->DrawState();
	++mCount;
	return next;
}
