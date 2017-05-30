#pragma once
#include "PhysicsMathBase.h"

class Allocator
{
public:
	Allocator(){};
	~Allocator(){};

	//メモリ確保時に呼ばれる
	//メモリを引数分確保し、ポインタを返す
	//確保に失敗したらNULLを返す
	virtual void *allocate(size_t bytes) = 0;

	//解放時に呼ばれる
	virtual void deallocate(void *p) = 0;
};

