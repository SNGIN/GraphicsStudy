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

	//uv�̏ꏊ
	uvLoc = glGetAttribLocation(m_shader->GetProgramName(), "tv");

	//uv���W���V�F�[�_���̕ϐ��ŎQ�Ƃł���悤�ɂ���
	glVertexAttribPointer(uvLoc, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(uvLoc);

	// �e�N�X�`�����j�b�g�� uniform �ϐ��̏ꏊ
	texLoc = glGetUniformLocation(m_shader->GetProgramName(), "tex");
}

void SimpleImageMaterial::UseTexture(){
	mtex->Use(texLoc,0);
	//�e�N�X�`���̏ꏊ���Q�Ƃł���悤�ɂ���
	/*glUniform1i(texLoc, 0);
	//�e�N�X�`���̌��т�
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mtex->Get());*/
}

void SimpleImageMaterial::OffTexture(){
	mtex->Release();
	//glBindTexture(GL_TEXTURE_2D, 0);
}