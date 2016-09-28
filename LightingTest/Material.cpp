#include "Material.h"


Material::Material(GLfloat(*amb), GLfloat(*diff), GLfloat(*spec), GLfloat *shi,Shader &shader)
{
	// 引数に初期値を設定する
	this->m_amb = amb;
	this->m_diff = diff;
	this->m_spec = spec;
	this->m_shi = shi;

	//シェーダーの選択
	attachShader(shader);
	shader.Use();

	// 材質のパラメータの uniform 変数の場所をセットする
	shader.loc_material.kamb = glGetUniformLocation(shader.GetProgramName(), "kamb");
	shader.loc_material.kdiff = glGetUniformLocation(shader.GetProgramName(), "kdiff");
	shader.loc_material.kspec = glGetUniformLocation(shader.GetProgramName(), "kspec");
	shader.loc_material.kshi = glGetUniformLocation(shader.GetProgramName(), "kshi");

	SetMaterial();
}

void Material::SetMaterial(){
	glUniform4fv(m_shader->loc_material.kamb, 1, m_amb);
	glUniform4fv(m_shader->loc_material.kdiff, 1, m_diff);
	glUniform4fv(m_shader->loc_material.kspec, 1, m_spec);
	glUniform1f(m_shader->loc_material.kshi, *m_shi);
}
