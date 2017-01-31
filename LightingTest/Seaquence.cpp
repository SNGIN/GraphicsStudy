#include "Seaquence.h"
#include "SeaquenceController.h"

Boot* Seaquence::Update(Boot* p)
{
	SeaquenceController* controller = dynamic_cast<SeaquenceController*>(p);
	//派生クラスのUpdateに任す
	return Update(controller);
}

Seaquence::~Seaquence()
{
}
