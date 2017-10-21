#include "SimpleImageMaterial.h"

static const GLfloat texuv[] = {
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,
};

SimpleImageMaterial::SimpleImageMaterial(Shader* shader, Texture* tex) :mtex(0)
{
	mtex = tex;
	m_shader = shader;
}


SimpleImageMaterial::~SimpleImageMaterial()
{
}

void SimpleImageMaterial::SetTexLoc(){

	//uvの場所
	uvLoc = glGetAttribLocation(m_shader->GetProgramName(), "tv");

	//uv座標をシェーダ内の変数で参照できるようにする
	glVertexAttribPointer(uvLoc, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(uvLoc);

	// テクスチャユニットの uniform 変数の場所
	texLoc = glGetUniformLocation(m_shader->GetProgramName(), "tex");
}

void SimpleImageMaterial::UseTexture(){
	mtex->Use(texLoc,0);
	//テクスチャの場所を参照できるようにする
	/*glUniform1i(texLoc, 0);
	//テクスチャの結びつけ
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mtex->Get());*/
}

void SimpleImageMaterial::OffTexture(){
	mtex->Release();
	//glBindTexture(GL_TEXTURE_2D, 0);
}