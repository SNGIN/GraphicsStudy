#include "Clear.h"
#include "GameSeaquenceController.h"
#include "Ready.h"
#include "Ending.h"


Clear::Clear() :mCount(0)
{
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
	controller->DrawState();
	std::cout << "Clear" << std::endl;
	++mCount;
	return next;
}
