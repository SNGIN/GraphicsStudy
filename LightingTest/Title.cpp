#include "Title.h"
#include "InputManager.h"
#include "SeaquenceController.h"
#include "GameSeaquenceController.h"

Title::Title()
{

}


Title::~Title()
{
	//タイトルで使ってるリソースの解放
}

Boot* Title::Update(SeaquenceController* controller){
	Boot* next = this;
	std::cout << "Title" << std::endl;
	if (InputManager::CheckInputSpace()){
		next = new GameSeaquenceController();
	}
	return next;
}