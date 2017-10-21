#include "File.h"
#include <fstream>
#include "Commonheader.h"

File::File(const char* filename) :mSize(0), mData(0)
{
	//�o�C�i���f�[�^��ǂݍ���ł���
	std::ifstream in(filename, std::ifstream::binary);
	if (in){
		//�|�C���^�����܂ňړ�
		in.seekg(0, std::ifstream::end);
		//�|�C���^�ʒu��ۑ��A�T�C�Y���m��
		mSize = static_cast< int >(in.tellg());
		//�n�܂�Ɉړ��A�ŏ�����ǂݍ���ł���
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