#include "Commonheader.h"
#pragma once

class Seaquence;

//�V�[�P���X���ړ������肷��R���g���[��
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

