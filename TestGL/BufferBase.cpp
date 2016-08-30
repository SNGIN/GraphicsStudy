#include "BufferBase.h"

//バッファへの参照が一つならtrue
bool BufferBase::last() const{
	return ref->count == 1;
}

bool BufferBase::newCounter(){
	// 唯一のオブジェクトかどうか調べる
	bool status(last());

	// 元の参照カウンタの管理対象から外す
	if (--ref->count == 0) delete ref;

	// 新しい参照カウンタを作成して, それに付け替える
	ref = new RefCounter;

	// 元のオブジェクトの状態を返す
	return status;
}
