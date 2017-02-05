#include "Pause.h"
#include "Play.h"
#include "Title.h"
#include "GameSeaquenceController.h"

Pause::Pause()
{
	std::cout << "Pause" << std::endl;
}


Pause::~Pause()
{
}

Boot* Pause::Update(GameSeaquenceController* controller){
	Boot* next = this;
	//スペース:再開
	//t:タイトルへ
	//b:ステージ選択
	//r:リセット
	if (InputManager::CheckInputP()){
		next = new Play;
	}
	else if (InputManager::CheckInputT()){
		next = new Title;
	}
	else if (InputManager::CheckInputB()){
		//ステージセレクトへ
	}
	else if (InputManager::CheckInputR()){
		//リセット
	}
	controller->DrawState();

	return next;
}