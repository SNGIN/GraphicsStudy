#include "Material.h"


Material::Material(GLfloat(*amb), GLfloat(*diff), GLfloat(*spec), GLfloat *shi,Shader &shader)
{
	// �����ɏ����l��ݒ肷��
	this->m_amb = amb;
	this->m_diff = diff;
	this->m_spec = spec;
	this->m_shi = shi;

	//�V�F�[�_�[�̑I��
	attachShader(shader);
}

void Material::SetMaterial(){
	glUniform4fv(m_shader->loc.kamb, 1, m_amb);
	glUniform4fv(m_shader->loc.kdiff, 1, m_diff);
	glUniform4fv(m_shader->loc.kspec, 1, m_spec);
	glUniform1f(m_shader->loc.kshi, *m_shi);
}
