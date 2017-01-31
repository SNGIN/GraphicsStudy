#include "GameSeaquence.h"
#include "GameSeaquenceController.h"

//派生クラスの挙動に任せる
Boot* GameSeaquence::Update(Boot* p){
	GameSeaquenceController* controller = dynamic_cast<GameSeaquenceController*>(p);
	return Update(controller);
}

GameSeaquence::~GameSeaquence()
{
}
