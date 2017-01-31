#pragma once
#include "Commonheader.h"


#ifdef DEBUG
	// �V�F�[�_�I�u�W�F�N�g�̃R���p�C�����ʂ�\������
	extern GLboolean printShaderInfoLog(GLuint shader, const char *str);
	
	// �V�F�[�_�I�u�W�F�N�g�̃����N���ʂ�\��
	extern GLboolean printProgramInfoLog(GLuint program);
#endif // DEBUG

	// �v���O�����I�u�W�F�N�g�̍쐬
	extern GLuint createProgram(const char *vsrc, const char *pv, const char *fsrc, const char *fc,
		const char *vert = "vertex shader", const char *frag = "fragment shader");

	// �V�F�[�_�̃\�[�X�t�@�C���̓ǂݍ���
	extern GLuint loadProgram(const char *vert, const char *pv, const char *frag, const char *fc);

