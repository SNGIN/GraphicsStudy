#include "Pause.h"
#include "Play.h"
#include "Title.h"
#include "GameSeaquenceController.h"

Pause::Pause()
{
	std::cout << "Pause" << std::endl;
}


Pause::~Pause()
{
}

Boot* Pause::Update(GameSeaquenceController* controller){
	Boot* next = this;
	//�X�y�[�X:�ĊJ
	//t:�^�C�g����
	//b:�X�e�[�W�I��
	//r:���Z�b�g
	if (InputManager::CheckInputP()){
		next = new Play;
	}
	else if (InputManager::CheckInputT()){
		next = new Title;
	}
	else if (InputManager::CheckInputB()){
		//�X�e�[�W�Z���N�g��
	}
	else if (InputManager::CheckInputR()){
		//���Z�b�g
	}
	controller->DrawState();

	return next;
}