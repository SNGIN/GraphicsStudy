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

	mLife = 2;
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
	return(mStageID >= FINALSTAGE);
}

Physics* GameSeaquenceController::GetPhysics(){
	return m_Physics;
}

State* GameSeaquenceController::GetState(){
	return mState;
}

void GameSeaquenceController::DrawState()const{
	mState->Draw();
}

void GameSeaquenceController::StartLoading(){
	//TODO:読み込みが重いのでリセットとかにするといい
	Common::Delete(mState);
	Common::Delete(m_Physics);

	m_Physics = new Physics();
	mState = new State(mStageID);
}

void GameSeaquenceController::GotoNextStage(){
	++mStageID;
}

int GameSeaquenceController::LifeNumber(){
	return mLife;
}

void GameSeaquenceController::ReduceLife(){
	--mLife;
}