#pragma once
#include "Allocator.h"

class DefaultAllocator:public Allocator
{
public:
	DefaultAllocator(){};
	~DefaultAllocator(){};

	//メモリ確保時に呼ばれる
	//メモリを引数分確保し、ポインタを返す
	//確保に失敗したらNULLを返す
	void *allocate(size_t bytes){
		return malloc(bytes);
	}

	//解放時に呼ばれる
	void deallocate(void *p){
		free(p);
	}
};