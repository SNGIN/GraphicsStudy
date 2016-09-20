#pragma once
#include "Commonheader.h"
#include "Buffer.h"

//���_�������N���X
class ShapePoints
{
	//���_�z��I�u�W�F�N�g
	GLuint vao;
	GLenum mode;

	//���_�o�b�t�@�I�u�W�F�N�g
	Buffer<GLfloat[3]> position;
	
	//���_�ʒu�̊m��
	void LoadPosition(GLuint nv, const GLfloat(*pos)[3], GLenum usage){
		// ���_�ʒu
		position.Load(GL_ARRAY_BUFFER, nv, pos, usage);
		// ���̃o�b�t�@�I�u�W�F�N�g�� index == 0 �� in �ϐ�������͂���
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
	}

public:
	void Use() const{
		glBindVertexArray(vao);
	}
	GLuint Get() const{
		return vao;
	}
	void SetMode(GLenum mode){
		this->mode = mode;
	}
	GLenum GetMode(){
		return this->mode;
	}

	void Send(GLuint nv, const GLfloat(*pos)[3], GLuint offset){
		position.Send(nv, pos, offset);
	}
	void Load(GLuint nv, const GLfloat(*pos)[3], GLenum usage = GL_STATIC_DRAW){
		LoadPosition(nv, pos, usage);
	}
	GLuint pbuf()const{
		return position.GetBuffer();
	}
	GLuint pnum()const{
		return position.GetNum();
	}

	ShapePoints(GLenum mode = 0){
		this->mode = mode;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
	}
	ShapePoints(GLuint nv, const GLfloat(*pos)[3], GLenum mode = GL_POINTS, GLenum usage = GL_STATIC_DRAW):ShapePoints(mode){
		this->mode = mode;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		LoadPosition(nv, pos, usage);
	}

	//�R�s�[�R���X�g���N�^.
	ShapePoints(const ShapePoints &o)
		: vao(o.vao), mode(o.mode)
	{
		glBindVertexArray(vao);
	}

	//������Z�q
	ShapePoints &operator=(const ShapePoints &o)
	{
		if (this != &o)
		{
			vao = o.vao;
			mode = o.mode;
			glBindVertexArray(vao);
			ShapePoints::operator=(o);
			position = o.position;
		}
		return *this;
	}

	virtual ~ShapePoints(){
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &vao);
	}
	//! \brief �|�C���g�̕`��.
	virtual void draw(GLint first = 0, GLsizei count = 0) const{
		// ���_�z��I�u�W�F�N�g���w�肷��
		Use();

		// �}�`��`�悷��
		glDrawArrays(this->mode, first, count > 0 ? count : pnum() - first);
	}
};

