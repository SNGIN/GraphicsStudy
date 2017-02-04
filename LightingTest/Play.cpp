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

	//���͂̃`�F�b�N
	InputManager::CheckInputMove();

	std::cout << "Play" << std::endl;

	bool cleared = state->hasCleared();
	bool missed = state->hasMissed();
	
	//-------------�m�F�p
	/*if (InputManager::CheckInputMoveUp()){
		cleared = true;
	}
	if (InputManager::CheckInputB()){
		missed = true;
	}*/
	//-------------�m�F�p

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

	//�I�u�W�F�N�g�̍X�V
	state->Update();
	//�`��
	state->Draw();

	return next;
}