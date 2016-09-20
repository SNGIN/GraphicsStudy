#pragma once
#include "RefCounter.h"

//�Q�Ƃ��Ǘ�����V�F�[�_�[��I�u�W�F�N���X�̊��N���X
class BufferBase
{
	RefCounter *ref;

protected:
	bool last() const;
	bool newCounter();
public:
	//�R���X�g���N�^
	BufferBase() :ref(new RefCounter){}
	//�R�s�[�R���X�g���N�^
	BufferBase(const BufferBase &o) :ref(o.ref){
		++ref->count;
	}
	//������Z�q
	BufferBase &operator=(const BufferBase &o){
		if (&o != this) ++(ref = o.ref)->count;
		return *this;
	}
	virtual ~BufferBase()
	{
		// �Q�ƃJ�E���^�������� 0 �ɂȂ�����Q�ƃJ�E���^���폜����
		if (--ref->count == 0) delete ref;
	}
};
