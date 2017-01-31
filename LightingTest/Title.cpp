#include "Title.h"
#include "InputManager.h"
#include "SeaquenceController.h"
#include "GameSeaquenceController.h"

Title::Title()
{

}


Title::~Title()
{
	//�^�C�g���Ŏg���Ă郊�\�[�X�̉��
}

Boot* Title::Update(SeaquenceController* controller){
	Boot* next = this;
	std::cout << "Title" << std::endl;
	if (InputManager::CheckInputSpace()){
		next = new GameSeaquenceController();
	}
	return next;
}