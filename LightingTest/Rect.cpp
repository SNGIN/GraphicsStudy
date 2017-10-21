#include "Rect.h"
#include "Window.h"

Rect::Rect()
{
}

Rect::Rect(GLfloat width, GLfloat height,Vector3 a_pos,bool a_billboard){
	// ��ƂȂ�`��
	static const GLfloat p[][3] =
	{
		{ -0.5f, -0.5f ,0.0f},
		{ 0.5f, -0.5f ,0.0f},
		{ 0.5f, 0.5f ,0.0f},
		{ -0.5f, 0.5f ,0.0f},
	};

	GLfloat tmpuv[6][2] = {
		{ 0.0f, 1.0f },
		{ 1.0f, 1.0f },
		{ 1.0f,1.0f },

		{ 0.0f, 0.0f },
	};

	// ��Ɨp�̃�����
	GLfloat norm[4][3];
	GLuint f[2][3];

	// ���_�ʒu�Ɩ@���x�N�g�������߂�
	for (int v = 0; v < 4; ++v)
	{
		uv[v][0] = tmpuv[v][0];
		uv[v][1] = tmpuv[v][1];

		m_vertPos[v][0] = p[v][0] * width;
		m_vertPos[v][1] = p[v][1] * height;
		m_vertPos[v][2] = 0.0f;

		norm[v][0] = 0.0f;
		norm[v][1] = 0.0f;
		norm[v][2] = 1.0f;
	
		
	}

	// ���_�ʒu�Ɩ@���x�N�g�������߂�
	for (int v = 0; v < 6; ++v)
	{
		uv[v][0] = tmpuv[v][0];
		uv[v][1] = tmpuv[v][1];
	}

	//�ǂ̒��_���ǂ̖ʂ�\���̂�
	f[1][0] = m_faces[3] = 0; f[1][1] = m_faces[4] = 1; f[1][2] = m_faces[5] = 2;
	f[0][0] = m_faces[0] = 3; f[0][1] = m_faces[1] = 0; f[0][2] = m_faces[2] = 2;

	mtriangle = new ShapeElements(4, p, norm, 2, f, GL_TRIANGLES);

	position = a_pos;

	billboard = a_billboard;
}

Rect::~Rect()
{
	Common::Delete(mtriangle);
}

GLfloat* Rect::GetVertPos(){
	return *m_vertPos;
}

GLfloat* Rect::GetVertPos(int i){
	return m_vertPos[i];
}

GLuint* Rect::GetFace(){
	return m_faces;
}

void Rect::SetMaterial(Material* mat){
	mMaterial = mat;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// ���_�̍��W�l tv �p�̃o�b�t�@�I�u�W�F�N�g
	glBindBuffer(GL_ARRAY_BUFFER, vao);
	glBufferData(GL_ARRAY_BUFFER, sizeof uv, uv, GL_STATIC_DRAW);

	//uv��e�N�X�`���̈ʒu��in�ϐ�����Q�Ƃł���悤�ɃZ�b�g����
	mMaterial->SetTexLoc();
}

void Rect::Draw(){
	if (mtriangle != NULL && mMaterial != NULL){
		//�g���V�F�[�_�ƃe�N�X�`���̎w��
		mMaterial->m_shader->Use();
		mMaterial->UseTexture();

		//�g�����_�o�b�t�@�I�u�W�F�N�g�̎w��
		mtriangle->Use();

		Matrix mm;
		mm.loadIdentity();
		mm.loadBillboard();
		mm *= Translate(0, 0, 30);

		Matrix mw;
		mw.loadIdentity();
		if (billboard){
			mw = Window::ReturnMV();
			mw.loadBillboard();
			mw *= Translate(0, 0, 30);
		}
		else{
			mw = Window::ReturnMV()*Translate(GetPos().getX(), GetPos().getY(), GetPos().getZ());
		}

		//�z�u
		mMaterial->m_shader->loadMatrix(Window::getMp(), mw,mm);
		//�`��
		mtriangle->Draw();

		mMaterial->OffTexture();

	}
}