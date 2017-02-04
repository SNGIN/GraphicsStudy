#include "Material.h"

//�ގ��̐F
static GLfloat ambColor[4] = { 0.6f, 0.6f, 0.6f, 1.0f };
static GLfloat diffColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
static GLfloat specColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
static GLfloat shiness = 30.0f;

Material::Material(Shader* shader)
{
	// �����ɏ����l��ݒ肷��
	this->m_amb = ambColor;
	this->m_diff = diffColor;
	this->m_spec = specColor;
	this->m_shi = &shiness;

	//�V�F�[�_�[�̑I��
	attachShader(shader);
	shader->Use();

	// �ގ��̃p�����[�^�� uniform �ϐ��̏ꏊ���Z�b�g����
	shader->loc_material.kamb = glGetUniformLocation(shader->GetProgramName(), "kamb");
	shader->loc_material.kdiff = glGetUniformLocation(shader->GetProgramName(), "kdiff");
	shader->loc_material.kspec = glGetUniformLocation(shader->GetProgramName(), "kspec");
	shader->loc_material.kshi = glGetUniformLocation(shader->GetProgramName(), "kshi");

	SetMaterial();
}

void Material::SetMaterial(){
	glUniform4fv(m_shader->loc_material.kamb, 1, m_amb);
	glUniform4fv(m_shader->loc_material.kdiff, 1, m_diff);
	glUniform4fv(m_shader->loc_material.kspec, 1, m_spec);
	glUniform1f(m_shader->loc_material.kshi, *m_shi);
}

Shader* Material::GetShader(){
	return m_shader;
}
