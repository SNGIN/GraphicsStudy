#include "BufferBase.h"

//�o�b�t�@�ւ̎Q�Ƃ���Ȃ�true
bool BufferBase::last() const{
	return ref->count == 1;
}

bool BufferBase::newCounter(){
	// �B��̃I�u�W�F�N�g���ǂ������ׂ�
	bool status(last());

	// ���̎Q�ƃJ�E���^�̊Ǘ��Ώۂ���O��
	if (--ref->count == 0) delete ref;

	// �V�����Q�ƃJ�E���^���쐬����, ����ɕt���ւ���
	ref = new RefCounter;

	// ���̃I�u�W�F�N�g�̏�Ԃ�Ԃ�
	return status;
}
