#include "GameSeaquenceController.h"
#include "SeaquenceController.h"
#include "Ending.h"
#include "Title.h"
#include "State.h"
#include "Ready.h"
#include "GameOver.h"
#include <sstream>


GameSeaquenceController::GameSeaquenceController() :mState(0), mStageID(0), 
mNextSeaquence(NEXT_NONE), mGameSeaquence(0)
{
	//Readyからスタート
	mGameSeaquence = new Ready();
}


GameSeaquenceController::~GameSeaquenceController()
{
	Common::Delete(mState);
	Common::Delete(mGameSeaquence);
}

//各ゲームのシーケンスUpdateを動かして、シーケンスを取得、取得したシーケンスが次のシーケンスなら
//遷移処理
Boot* GameSeaquenceController::Update(GrandController*){
	Boot* next = this;
	Boot* nextGameSeaquence = mGameSeaquence->Update(this);
	//遷移判定
	if (nextGameSeaquence != mGameSeaquence){
		GameSeaquence* casted = dynamic_cast<GameSeaquence*>(nextGameSeaquence);
		if (casted){
			Common::Delete(mGameSeaquence);
			mGameSeaquence = casted;
		}
		else{
			next = nextGameSeaquence;
		}
		casted = 0;
	}

	return next;
}

bool GameSeaquenceController::HasFinalStageCleard()const{
	return(mStageID > FINALSTAGE);
}

void GameSeaquenceController::DrawState()const{
	mState->Draw();
}

void GameSeaquenceController::StartLoading(){
	Common::Delete(mState);
	mState = new State(mStageID);
}

void GameSeaquenceController::GotoNextStage(){
	++mStageID;
}

int GameSeaquenceController::LifeNumber(){
	return mLifeNumber;
}