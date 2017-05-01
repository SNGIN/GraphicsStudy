#include "Material.h"


Material::Material(Shader* shader,GLfloat* ambColor,GLfloat* diffColor,GLfloat* specColor,GLfloat* shiness)
{
	m_Light = new Light();
	// 引数に初期値を設定する
	this->m_amb = ambColor;
	this->m_diff = diffColor;
	this->m_spec = specColor;
	this->m_shi = shiness;

	//シェーダーの選択
	attachShader(shader);
	shader->Use();

	//光パラメータのuniformの場所
	shader->loc_light.lamb = glGetUniformLocation(shader->GetProgramName(), "lamb");
	shader->loc_light.ldiff = glGetUniformLocation(shader->GetProgramName(), "ldiff");
	shader->loc_light.lspec = glGetUniformLocation(shader->GetProgramName(), "lspec");
	shader->loc_light.pl = glGetUniformLocation(shader->GetProgramName(), "pl");
	SetLight();

	// 材質のパラメータの uniform 変数の場所をセットする
	shader->loc_material.kamb = glGetUniformLocation(shader->GetProgramName(), "kamb");
	shader->loc_material.kdiff = glGetUniformLocation(shader->GetProgramName(), "kdiff");
	shader->loc_material.kspec = glGetUniformLocation(shader->GetProgramName(), "kspec");
	shader->loc_material.kshi = glGetUniformLocation(shader->GetProgramName(), "kshi");

	SetMaterial();
}

Material::~Material(){
	Common::Delete(m_amb);
	Common::Delete(m_diff);
	Common::Delete(m_spec);
	Common::Delete(m_shi);

	Common::Delete(m_shader);
	Common::Delete(m_Light);
}

void Material::SetLight(){
	glUniform4fv(m_shader->loc_light.lamb, 1, m_Light->GetAmb());
	glUniform4fv(m_shader->loc_light.ldiff, 1, m_Light->GetDiff());
	glUniform4fv(m_shader->loc_light.lspec, 1, m_Light->GetSpec());
	glUniform4fv(m_shader->loc_light.pl, 1, m_Light->GetPos());
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
