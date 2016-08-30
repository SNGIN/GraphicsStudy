#pragma once

//メモリへの参照をカウントする際に使用
class RefCounter
{
	friend class BufferBase;
	unsigned int count;
public:
	RefCounter():count(1){};
	~RefCounter(){};
};

