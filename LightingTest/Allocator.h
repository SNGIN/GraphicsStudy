#pragma once
#include "PhysicsMathBase.h"

class Allocator
{
public:
	Allocator(){};
	~Allocator(){};

	//�������m�ێ��ɌĂ΂��
	//���������������m�ۂ��A�|�C���^��Ԃ�
	//�m�ۂɎ��s������NULL��Ԃ�
	virtual void *allocate(size_t bytes) = 0;

	//������ɌĂ΂��
	virtual void deallocate(void *p) = 0;
};

