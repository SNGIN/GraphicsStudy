#pragma once
#include "RefCounter.h"

//参照を管理するシェーダーやオブジェクラスの基底クラス
class BufferBase
{
	RefCounter *ref;

protected:
	bool last() const;
	bool newCounter();
public:
	//コンストラクタ
	BufferBase() :ref(new RefCounter){}
	//コピーコンストラクタ
	BufferBase(const BufferBase &o) :ref(o.ref){
		++ref->count;
	}
	//代入演算子
	BufferBase &operator=(const BufferBase &o){
		if (&o != this) ++(ref = o.ref)->count;
		return *this;
	}
	virtual ~BufferBase()
	{
		// 参照カウンタを減じて 0 になったら参照カウンタを削除する
		if (--ref->count == 0) delete ref;
	}
};

