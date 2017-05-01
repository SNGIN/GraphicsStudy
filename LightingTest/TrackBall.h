#pragma once
#include "Commonheader.h"
#include "Quaternion.h"

/*
** �g���b�N�{�[������
*/
class TrackBall
{
	int cx, cy;                             // �h���b�O�J�n�ʒu
	bool drag;                              // �h���b�O�����ۂ�
	float sx, sy;                           // �}�E�X�̐�Έʒu���E�B���h�E���ł̑��Έʒu�̊��Z�W��
	const float rotateSpeed = 0.1;
	Quaternion cq;                        // ��]�̏����l (�l����)
	Quaternion tq;                        // �h���b�O���̉�] (�l����)
	GLfloat rt[16];                         // ��]�̕ϊ��s��

public:

	// �f�X�g���N�^
	virtual ~TrackBall(void) {}

	// �R���X�g���N�^
	TrackBall(void);

	// �g���b�N�{�[�������͈͎̔w��
	//    �E�B���h�E�̃��T�C�Y���ɌĂяo��
	void Region(int w, int h);

	// �g���b�N�{�[�������̊J�n
	//    �}�E�X�̃h���b�O�J�n���i�}�E�X�{�^�����������Ƃ��j�ɌĂяo��
	void Start(int x, int y);

	// ��]�̕ϊ��s��̌v�Z
	//    �}�E�X�̃h���b�O���ɌĂяo��
	void Motion(int x, int y);

	// �g���b�N�{�[�������̒�~
	//    �}�E�X�̃h���b�O�I�����i�}�E�X�{�^���𗣂����Ƃ��j�ɌĂяo��
	void Stop(int x, int y);

	// ���݂̉�]�̕ϊ��s������o��
	const GLfloat *Get(void) const
	{
		return rt;
	}
};

