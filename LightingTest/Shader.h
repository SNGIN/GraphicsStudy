#pragma once
#include "Commonheader.h"
#include "BufferBase.h"
#include "Texture.h"

//�ގ����̃V�F�[�_�[�\�[�X�ł̏ꏊ
struct MaterialLoc
{
	GLint kamb;       // �����̔��ˌW���� uniform �ϐ��̏ꏊ
	GLint kdiff;      // �g�U���ˌW���� uniform �ϐ��̏ꏊ
	GLint kspec;      // ���ʔ��ˌW���� uniform �ϐ��̏ꏊ
	GLint kshi;       // �P���W���� uniform �ϐ��̏ꏊ
};

//�ϊ��s��̃V�F�[�_�[�\�[�X�ł̏ꏊ
struct MatrixLoc
{
	GLint mc;
	GLint mw;
	GLint mg;         // ���f���r���[�ϊ��̖@���ϊ��s��� uniform �ϐ��̏ꏊ
};

static GLchar *ReadShaderSource(const char *name);

extern GLuint LoadShader(const char *vert, const char *frag = NULL, const char *geom = NULL,
	int nvarying = 0, const char *varyings[] = NULL);

#ifdef DEBUG
// �V�F�[�_�I�u�W�F�N�g�̃R���p�C�����ʂ�\������
extern GLboolean printShaderInfoLog(GLuint shader, const char *str);

// �V�F�[�_�I�u�W�F�N�g�̃����N���ʂ�\��
extern GLboolean printProgramInfoLog(GLuint program);
#endif // DEBUG

// �V�F�[�_�I�u�W�F�N�g�̍쐬
extern GLuint CreateShader(const char *vsrc, const char *fsrc, const char *gsrc,
	GLint nvarying, const char **varyings, const char *vtext, const char *ftext, const char *gtext);

//�V�F�[�_�[�N���X(���C���ŃC���X�^���X������A�g�p����}�e���A���ƕR�Â�����(�}�e���A���N���X�̃����o�ϐ��Ƃ���))
class Shader :public BufferBase{

	//�V�F�[�_�[�v���O������
	GLuint program;

public:

	MaterialLoc loc_material;
	MatrixLoc loc_matrix;

	//�f�X�g���N�^
	~Shader(){
		//�Q�Ƃ��Ă�I�u�W�F�N�g����Ȃ�V�F�[�_���폜
		if (program != 0 && last()){
			glUseProgram(0);
			glDeleteProgram(program);
		}
	}
	Shader(){}

	//��������̃R���X�g���N�^
	Shader(const char *vert, const char *frag = 0, const char *geom = 0,
		int nvarying = 0, const char **varyings = 0) :program(LoadShader(vert, frag, geom, nvarying, varyings)){
		
		// �ϊ��s��� uniform �ϐ��̏ꏊ
		loc_matrix.mc = glGetUniformLocation(program, "mc");
		loc_matrix.mw = glGetUniformLocation(program, "mw");
		// �ϊ��s��� uniform �ϐ��̏ꏊ
		loc_matrix.mg = glGetUniformLocation(program, "mg");
	}

	//�R�s�[�R���X�g���N�^
	Shader(const Shader &o) :BufferBase(o), program(o.program){}

	//������Z�q
	Shader &operator=(const Shader &o){
		if (&o != this){
			BufferBase::operator=(o);
			program = o.program;
		}
		return *this;
	}

	//�V�F�[�_�v���O������o�^
	void SetProgram(GLuint newProgram){
		if (program != 0 && newCounter()){
			glUseProgram(0);
			glDeleteProgram(program);
		}
		program = newProgram;
	}

	//�V�F�[�_�̃\�[�X��ǂ�Ńv���O�����I�u�W�F�N�g�ƕR�Â�
	void load(const char *vert, const char *frag = 0, const char *geom = 0,
		GLint nvarying = 0, const char **varyings = 0)
	{
		SetProgram(LoadShader(vert, frag, geom, nvarying, varyings));
	}

	void Use()const{
		glUseProgram(program);
	}

	void EndUse()const{
		glUseProgram(0);
	}

	GLuint GetProgramName()const{
		return program;
	}

	//�ϊ��s��,mp=���e�ϊ��s�� mw ���f���r���[�ϊ��s��
	virtual void loadMatrix(Matrix mp, Matrix mw);

	virtual void UseSimpleShader(Texture tex){};
};