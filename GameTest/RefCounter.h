#pragma once

//�������ւ̎Q�Ƃ��J�E���g����ۂɎg�p
class RefCounter
{
	friend class BufferBase;
	unsigned int count;
public:
	RefCounter():count(1){};
	~RefCounter(){};
};

