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
	//Ready����X�^�[�g
	mGameSeaquence = new Ready();

	mLife = 2;
}


GameSeaquenceController::~GameSeaquenceController()
{
	Common::Delete(mState);
	Common::Delete(mGameSeaquence);
}

//�e�Q�[���̃V�[�P���XUpdate�𓮂����āA�V�[�P���X���擾�A�擾�����V�[�P���X�����̃V�[�P���X�Ȃ�
//�J�ڏ���
Boot* GameSeaquenceController::Update(GrandController*){
	Boot* next = this;
	Boot* nextGameSeaquence = mGameSeaquence->Update(this);
	//�J�ڔ���
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
	//TODO:�ǂݍ��݂��d���̂Ń��Z�b�g�Ƃ��ɂ���Ƃ���
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