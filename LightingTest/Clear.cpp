#include "Clear.h"
#include "GameSeaquenceController.h"
#include "Ready.h"
#include "Ending.h"


Clear::Clear() :mCount(0)
{
}


Clear::~Clear()
{
	//Imageリソースの開放
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
	//描画
	controller->DrawState();
	std::cout << "Clear" << std::endl;
	++mCount;
	return next;
}
