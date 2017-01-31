#include "Seaquence.h"
#include "SeaquenceController.h"

Boot* Seaquence::Update(Boot* p)
{
	SeaquenceController* controller = dynamic_cast<SeaquenceController*>(p);
	//”h¶ƒNƒ‰ƒX‚ÌUpdate‚É”C‚·
	return Update(controller);
}

Seaquence::~Seaquence()
{
}
