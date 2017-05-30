#include "Clear.h"
#include "GameSeaquenceController.h"
#include "Ready.h"
#include "Ending.h"


Clear::Clear() :mCount(0)
{
	std::cout << "Clear" << std::endl;
}


Clear::~Clear()
{
	//Image���\�[�X�̊J��
}

Boot* Clear::Update(GameSeaquenceController* controller){
	Boot* next = this;
	if (mCount == 60){
		if (controller->HasFinalStageCleard()){
			next = new Ending;
		}
		else{
			next = new Ready;
		}
	}
	//�`��
	controller->DrawStateGame();
	++mCount;
	return next;
}
