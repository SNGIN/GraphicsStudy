#version 150 core
#extension GL_ARB_explicit_attrib_location : enable

// ���X�^���C�U����󂯎�钸�_�����̕�Ԓl
in vec4 iamb;                                       // �����̔��ˌ����x
in vec4 idiff;                                      // �g�U���ˌ����x
in vec4 ispec;                                      // ���ʔ��ˌ����x

float sum = 0; 

// �t���[���o�b�t�@�ɏo�͂���f�[�^
layout (location = 0) out vec4 fc;                  // �t���O�����g�̐F

void main(void)
{
	fc = idiff + iamb + ispec;
}