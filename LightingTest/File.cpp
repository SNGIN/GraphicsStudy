#include "File.h"
#include <fstream>
#include "Commonheader.h"

File::File(const char* filename) :mSize(0), mData(0)
{
	//バイナリデータを読み込んでいく
	std::ifstream in(filename, std::ifstream::binary);
	if (in){
		//ポインタを後ろまで移動
		in.seekg(0, std::ifstream::end);
		//ポインタ位置を保存、サイズを確保
		mSize = static_cast< int >(in.tellg());
		//始まりに移動、最初から読み込んでいく
		in.seekg(0, std::ifstream::beg);
		mData = new char[mSize];
		in.read(mData, mSize);
	}
}

File::File(){

}

File::~File()
{
	Common::Delete(mData);
}

int File::GetSize() const {
	return mSize;
}

const char* File::GetData() const {
	return mData;
}