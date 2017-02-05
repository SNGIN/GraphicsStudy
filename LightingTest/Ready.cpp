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
		//レディ
		std::cout << "Ready" << std::endl;
	}

	if (mCount >= 120){
		//ゴー
		std::cout << "Go" << std::endl;
		next = new Play;
	}
	else if (mCount >= 60){
	}
	else{

	}
	//描画
	controller->DrawState();
	++mCount;
	return next;
}
