#pragma once
#include "Commonheader.h"
#include "InputManager.h"

//�V�[�P���X�̌��N���X(�h���N���X��Update���X�V���Ă���)
class Boot
{
public:
	virtual ~Boot(){} //�Ȃɂ����Ȃ��̂ł���ł���
	virtual Boot* Update(Boot*) = 0;
};

