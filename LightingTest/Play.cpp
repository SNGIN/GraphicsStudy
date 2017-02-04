#include "Play.h"
#include "GameSeaquenceController.h"
#include "State.h"
#include "Pause.h"
#include "Clear.h"
#include "Failure.h"

Play::Play()
{
}


Play::~Play()
{
}

Boot* Play::Update(GameSeaquenceController* controller){
	Boot* next = this;
	State* state = controller->GetState();

	//入力のチェック
	InputManager::CheckInputMove();

	std::cout << "Play" << std::endl;

	bool cleared = state->hasCleared();
	bool missed = state->hasMissed();
	
	//-------------確認用
	/*if (InputManager::CheckInputMoveUp()){
		cleared = true;
	}
	if (InputManager::CheckInputB()){
		missed = true;
	}*/
	//-------------確認用

	if (cleared){
		controller->GotoNextStage();
		next = new Clear;
	}
	else if (missed){
		controller->ReduceLife();
		next = new Failure;
	}

	if (InputManager::CheckInputP()){
		next = new Pause;
	}

	//オブジェクトの更新
	state->Update();
	//描画
	state->Draw();

	return next;
}