#pragma once
#include "Commonheader.h"

static class Shader
{
private:
	Shader();
	~Shader();
public:
#ifdef DEBUG
	// �V�F�[�_�I�u�W�F�N�g�̃R���p�C�����ʂ�\������
	GLboolean printShaderInfoLog(GLuint shader, const char *str);
	
	// �V�F�[�_�I�u�W�F�N�g�̃����N���ʂ�\��
	GLboolean printProgramInfoLog(GLuint program);
#endif // DEBUG

	// �ǂݍ��񂾃�������Ԃ�
	GLchar *readShaderSource(const char *name);

	// �v���O�����I�u�W�F�N�g�̍쐬
	GLuint createProgram(const char *vsrc, const char *pv, const char *fsrc, const char *fc,
		const char *vert = "vertex shader", const char *frag = "fragment shader");

	// �V�F�[�_�̃\�[�X�t�@�C���̓ǂݍ���
	GLuint loadProgram(const char *vert, const char *pv, const char *frag, const char *fc);
};

