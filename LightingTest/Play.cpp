#include "Play.h"
#include "GameSeaquenceController.h"
#include "State.h"
#include "Pause.h"
#include "Clear.h"
#include "Failure.h"

Play::Play()
{
	std::cout << "Play" << std::endl;
}


Play::~Play()
{
}

Boot* Play::Update(GameSeaquenceController* controller){
	Boot* next = this;
	State* state = controller->GetState();

	//入力のチェック
	InputManager::CheckInputMove();

	bool cleared = state->hasCleared();
	bool missed = state->hasMissed();

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
	//物理シミュレーションの更新

	//描画
	state->Draw();

	return next;
}