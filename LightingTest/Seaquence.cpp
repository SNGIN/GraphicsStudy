#include "Seaquence.h"
#include "SeaquenceController.h"

Boot* Seaquence::Update(Boot* p)
{
	SeaquenceController* controller = dynamic_cast<SeaquenceController*>(p);
	//�h���N���X��Update�ɔC��
	return Update(controller);
}

Seaquence::~Seaquence()
{
}
