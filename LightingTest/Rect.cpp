#include "Rect.h"
#include "Window.h"

Rect::Rect()
{
}

Rect::Rect(GLfloat width, GLfloat height){
	// ��ƂȂ�`��
	static const GLfloat p[][2] =
	{
		{ -0.5f, -0.5f },
		{ 0.5f, -0.5f },
		{ 0.5f, 0.5f },
		{ -0.5f, 0.5f },
	};

	GLfloat tmpuv[4][2] = {
		{ 0.0f, 1.0f },
		{ 1.0f, 1.0f },
		{ 1.0f, 0.0f },
		{ 0.0f, 1.0f },
	};

	// ��Ɨp�̃�����
	GLfloat pos[4][3];
	GLfloat norm[4][3];

	// ���_�ʒu�Ɩ@���x�N�g�������߂�
	for (int v = 0; v < 4; ++v)
	{
		uv[v][0] = tmpuv[v][0];
		uv[v][1] = tmpuv[v][1];

		pos[v][0] = p[v][0] * width;
		pos[v][1] = p[v][1] * height;
		pos[v][2] = 0.0f;

		norm[v][0] = 0.0f;
		norm[v][1] = 0.0f;
		norm[v][2] = 1.0f;
	}

	mtriangle = new ShapeTriangle(4, pos, norm, GL_TRIANGLE_FAN);
}

Rect::~Rect()
{
	Common::Delete(mtriangle);
}

void Rect::SetMaterial(Material* mat){
	mMaterial = mat;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// ���_�̍��W�l tv �p�̃o�b�t�@�I�u�W�F�N�g
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof uv, uv, GL_STATIC_DRAW);

	//uv��e�N�X�`���̈ʒu��in�ϐ�����Q�Ƃł���悤�ɃZ�b�g����
	mMaterial->SetTexLoc();
}

void Rect::Draw(){
	if (mtriangle != NULL && mMaterial != NULL){
		//�g�����_�o�b�t�@�I�u�W�F�N�g�̎w��
		mtriangle->Use();
		//�g���V�F�[�_�ƃe�N�X�`���̎w��
		mMaterial->m_shader->Use();
		mMaterial->UseTexture();
		//�z�u
		mMaterial->m_shader->loadMatrix(Window::getMp(), Window::ReturnMV()*Translate(0.0f, 0.0f, 0.0f));
		//�`��
		mtriangle->draw();
	}
}