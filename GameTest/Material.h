#pragma once
#include "Shader.h"

//�ގ����Ǝg�p����V�F�[�_��ێ�����N���X
class Material
{
	//�����̔��ˌW��
	GLfloat(*m_amb);
	//�g�U���ˌW��
	GLfloat(*m_diff);
	//���ʔ��ˌW��
	GLfloat(*m_spec);
	//�P���W��
	GLfloat*m_shi;


public:
	Material(){};
	~Material(){};

	//�g�p����V�F�[�_
	Shader *m_shader;

	//��������̃R���X�g���N�^�ōގ��̐ݒ�ƃV�F�[�_�[�̑I������������
	//(���łɃ����o�̃V�F�[�_�N���X�ɏ���n��)
	Material(GLfloat *amb, GLfloat*diff, GLfloat *spec, GLfloat *shi,Shader &shader);

	void attachShader(Shader &shader){
		this->m_shader = &shader;
	}

	void attachShader(Shader *shader){
		this->m_shader = shader;
	}

	void SetMaterial();

};
