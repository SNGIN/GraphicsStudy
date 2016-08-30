#pragma once
#include "Shader.h"

//�ގ����Ǝg�p����V�F�[�_��ێ�����N���X
class Material
{
	//�����̔��ˌW��
	GLfloat(*amb)[4];
	//�g�U���ˌW��
	GLfloat(*diff)[4];
	//���ʔ��ˌW��
	GLfloat(*spec)[4];
	//�P���W��
	GLfloat*shi;
	//�g�p����V�F�[�_
	Shader *m_shader;

public:
	Material(){};
	~Material(){};

	//��������̃R���X�g���N�^�ōގ��̐ݒ�ƃV�F�[�_�[�̑I������������
	//(���łɃ����o�̃V�F�[�_�N���X�ɏ���n��)

	void attachShader(Shader &shader){
		this->m_shader = &shader;
	}

	void attachShader(Shader *shader){
		this->m_shader = shader;
	}

};

