#include "Failure.h"
#include "GameSeaquenceController.h"
#include "Ready.h"
#include "GameOver.h"

Failure::Failure()
{
	std::cout << "failure" << std::endl;
	mCount = 0;
}


Failure::~Failure()
{
}

//ƒ~ƒX•\Ž¦
Boot* Failure::Update(GameSeaquenceController* controller){
	Boot* next = this;
	if (mCount >= 60){
		if (controller->LifeNumber() <= 0){
			next = new GameOver;
		}
		else{
			next = new Ready;
		}
	}
	//•`‰æ
	++mCount;
	return next;
}