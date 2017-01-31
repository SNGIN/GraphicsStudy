#include "Ready.h"
#include "GameSeaquenceController.h"
#include "Play.h"
#include "Commonheader.h"

Ready::Ready() :mCount(0), mStarted(false)
{
	//イメージを作って出す
}


Ready::~Ready()
{
	//イメージリソースの破棄
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
		//ゴー
		std::cout << "Go" << std::endl;
	}
	else{
		//レディ
		std::cout << "Ready" << std::endl;
	}
	//描画
	controller->DrawState();
	++mCount;
	return next;
}
