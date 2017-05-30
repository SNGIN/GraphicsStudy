#pragma once
#include "Allocator.h"

class DefaultAllocator:public Allocator
{
public:
	DefaultAllocator(){};
	~DefaultAllocator(){};

	//�������m�ێ��ɌĂ΂��
	//���������������m�ۂ��A�|�C���^��Ԃ�
	//�m�ۂɎ��s������NULL��Ԃ�
	void *allocate(size_t bytes){
		return malloc(bytes);
	}

	//������ɌĂ΂��
	void deallocate(void *p){
		free(p);
	}
};