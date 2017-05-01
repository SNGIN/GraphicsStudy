#include "TrackBall.h"


TrackBall::TrackBall(void)
{
	// �h���b�O���ł͂Ȃ�
	drag = false;

	// �P�ʃN�H�[�^�[�j�I��
	cq.loadIdentity();

	// ��]�s��̏�����
	cq.getMatrix(rt);
}

/*
** �ȈՃg���b�N�{�[�������F�g���b�N�{�[������̈�̐ݒ�
**
**    Reshape �R�[���o�b�N (resize) �̒��Ŏ��s����
**    (w, h): �E�B���h�E�T�C�Y
*/
void TrackBall::Region(int w, int h)
{
	// �}�E�X�|�C���^�ʒu�̃E�B���h�E���̑��ΓI�ʒu�ւ̊��Z�p
	sx = 1.0f / static_cast<float>(w);
	sy = 1.0f / static_cast<float>(h);
}

/*
** �ȈՃg���b�N�{�[�������F�h���b�O�J�n���̏���
**
**    �}�E�X�{�^�����������Ƃ��Ɏ��s����
**    (x, y): ���݂̃}�E�X�ʒu
*/
void TrackBall::Start(int x, int y)
{
	// �h���b�O�J�n
	drag = true;

	// �h���b�O�J�n�_���L�^����
	cx = x;
	cy = y;
}

/*
** �ȈՃg���b�N�{�[�������F�h���b�O���̏���
**
**    �}�E�X�̃h���b�O���Ɏ��s����
**    (x, y): ���݂̃}�E�X�ʒu
*/
void TrackBall::Motion(int x, int y)
{
	if (drag)
	{
		float dx, dy, a;

		// �}�E�X�|�C���^�̈ʒu�̃h���b�O�J�n�ʒu����̕ψ�
		dx = ((x - cx) * sx)/1000;
		dy = ((y - cy) * sy)/1000;

		// �}�E�X�|�C���^�̈ʒu�̃h���b�O�J�n�ʒu����̋���
		a = sqrt(dx * dx + dy * dy)*rotateSpeed;

		if (a != 0.0)
		{
			// ���݂̉�]�̎l�����ɍ�����l�������|���č�������
			tq = RotateQuaternion(dy, dx, 0.0f, 0.01) * cq;
			// ���������l���������]�̕ϊ��s������߂�
			tq.getMatrix(rt);
		}
		// ���݂̉�]��\���l�����𐳋K�����ĕۑ�����
		cq = tq.normalize();
	}
}

/*
** �ȈՃg���b�N�{�[�������F��~���̏���
**
**    �}�E�X�{�^���𗣂����Ƃ��Ɏ��s����
**    (x, y): ���݂̃}�E�X�ʒu
*/
void TrackBall::Stop(int x, int y)
{
	// �h���b�O�I���_�ɂ������]�����߂�
	Motion(x, y);

	// ���݂̉�]��\���l�����𐳋K�����ĕۑ�����
	cq = tq.normalize();

	// �h���b�O�I��
	drag = false;
}