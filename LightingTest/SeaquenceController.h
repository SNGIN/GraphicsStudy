#include "Commonheader.h"
#pragma once

class Seaquence;

//シーケンスを移動したりするコントローラ
class SeaquenceController
{
public:
	void Update();

	static void Create();
	static void Destroy();
	static SeaquenceController* instance();

private:
	SeaquenceController();
	~SeaquenceController();

	Seaquence* mSeaquence;

	static SeaquenceController* mInstance;
};

