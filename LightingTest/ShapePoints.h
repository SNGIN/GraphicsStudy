#pragma once
#include "Commonheader.h"
#include "Buffer.h"

//�`��̊��N���X
class Shape
{
	//���_�z��I�u�W�F�N�g
	GLuint vao;
	GLenum mode;

public:

	//! \brief �f�X�g���N�^.
	virtual ~Shape()
	{
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &vao);
	}

	//! \brief �R���X�g���N�^.
	//!   \param mode ��{�}�`�̎��.
	Shape(GLenum mode = 0)
	{
		this->mode = mode;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
	}

	//! \brief �R�s�[�R���X�g���N�^.
	Shape(const Shape &o)
		: vao(o.vao), mode(o.mode)
	{
		glBindVertexArray(vao);
	}

	// ������Z�q
	Shape &operator=(const Shape &o)
	{
		if (this != &o)
		{
			vao = o.vao;
			mode = o.mode;
			glBindVertexArray(vao);
		}
		return *this;
	}

	//! \brief ���̐}�`�̒��_�z��I�u�W�F�N�g���w�肷��.
	void use() const
	{
		glBindVertexArray(vao);
	}

	//! \brief ���_�z��I�u�W�F�N�g�������o��.
	//!   \return ���_�z��I�u�W�F�N�g��.
	GLuint get() const
	{
		return vao;
	}

	//! \brief ��{�}�`�̐ݒ�.
	//!   \param mode ��{�}�`�̎��.
	void setMode(GLenum mode)
	{
		this->mode = mode;
	}

	//! \brief ��{�}�`�̌���.
	//!   \return ���̒��_�z��I�u�W�F�N�g�̊�{�}�`�̎��.
	GLenum getMode() const
	{
		return this->mode;
	}

	//! \brief �}�`�̕`��.
	//!   \brief ���̌`���`�悷��葱�����I�[�o�[���C�h����.
	virtual void draw(GLint first = 0, GLsizei count = 0) const = 0;
};

//�ʒu���������_�N���X
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
	ShapePoints(GLenum mode = GL_POINTS){
		this->mode = mode;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
	}
	ShapePoints(GLuint nv, const GLfloat(*pos)[3], GLenum mode = GL_POINTS, GLenum usage = GL_STATIC_DRAW){
		this->mode = mode;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		LoadPosition(nv, pos, usage);
	}

	//�R�s�[�R���X�g���N�^.
	ShapePoints(const ShapePoints &o) :position(o.position), vao(o.vao), mode(o.mode){
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

			position = o.position;
		}
		return *this;
	}
	virtual ~ShapePoints(){
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &vao);
	}

	//! \brief ���̐}�`�̒��_�z��I�u�W�F�N�g���w�肷��.
	void Use() const
	{
		glBindVertexArray(vao);
	}

	//! \brief ��{�}�`�̐ݒ�.
	//!   \param mode ��{�}�`�̎��.
	void SetMode(GLenum mode)
	{
		this->mode = mode;
	}

	//! \brief ��{�}�`�̌���.
	//!   \return ���̒��_�z��I�u�W�F�N�g�̊�{�}�`�̎��.
	GLenum GetMode() const
	{
		return this->mode;
	}
	
	void Send(GLuint nv, const GLfloat(*pos)[3], GLuint offset){
		position.Send(nv, pos, offset);
	}
	void Load(GLuint nv, const GLfloat(*pos)[3], GLenum usage = GL_STATIC_DRAW){
		LoadPosition(nv, pos, usage);
	}
	GLuint GetPosBuf()const{
		return position.GetBuffer();
	}
	GLuint GetPosNum()const{
		return position.GetNum();
	}

	//! \brief �|�C���g�̕`��.
	virtual void Draw(GLint first = 0, GLsizei count = 0) const{
		// ���_�z��I�u�W�F�N�g���w�肷��
		Use();

		// �}�`��`�悷��
		glDrawArrays(GetMode(), first, count > 0 ? count : GetPosNum() - first);
	}
};

