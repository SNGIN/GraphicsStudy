#include "GameSeaquence.h"
#include "GameSeaquenceController.h"

//�h���N���X�̋����ɔC����
Boot* GameSeaquence::Update(Boot* p){
	GameSeaquenceController* controller = dynamic_cast<GameSeaquenceController*>(p);
	return Update(controller);
}

GameSeaquence::~GameSeaquence()
{
}
