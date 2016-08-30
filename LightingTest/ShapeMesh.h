#pragma once
#include "ShapeTriangle.h"

class ShapeMesh:ShapeTriangle
{
	Buffer<GLuint[3]> index;

public:
	ShapeMesh(){};
	~ShapeMesh(){};

	ShapeMesh(GLuint nv, const GLfloat(*pos)[3], const GLfloat(*norm)[3],
		GLuint nf, const GLuint(*face)[3], GLenum usage = GL_STATIC_DRAW):ShapeTriangle(nv,pos,norm,usage){
		index.Load(GL_ELEMENT_ARRAY_BUFFER, nf, face);
	}

	//�R�s�[�R���X�g���N�^
	ShapeMesh(const ShapeMesh &o) :
		ShapeTriangle(o), index(o.index){}

	ShapeMesh &operator=(const ShapeMesh &o){
		if (&o != this){
			ShapeTriangle::operator=(o);
			index = o.index;
		}
		return *this;
	}

	//�����o�[�ϐ��̃Q�b�^�[
	GLuint Pos(){

	}

	//�o�b�t�@�I�u�W�F�N�g�ɒ��_�̃C���f�b�N�X�f�[�^��]��
	//! \brief �����̃o�b�t�@�I�u�W�F�N�g�ɒ��_�̈ʒu�f�[�^�Ɩ@���f�[�^��]������.
	//!   \param nv �]�����钸�_�̈ʒu�f�[�^�̐� (0 �Ȃ�o�b�t�@�S��).
	//!   \param pos �]�����̒��_�̈ʒu�f�[�^���i�[����ĂĂ���̈�̐擪�̃|�C���^.
	//!   \param norm �]�����̒��_�̖@���f�[�^���i�[����ĂĂ���̈�̐擪�̃|�C���^.
	//!   \param offset �]����̃o�b�t�@�I�u�W�F�N�g�̐擪�̗v�f�ԍ�.
	void Send(GLuint nf,const GLuint (*face)[3],GLuint offset = 0){
		index.Send(nf, face, offset);
	}

	void Load(GLuint nv, const GLfloat(*pos)[3], const GLfloat(*norm)[3],
		GLuint nf, GLuint(*face)[3], GLenum usage = GL_STATIC_DRAW){
		
		ShapeTriangle::Load(nv, pos, norm, usage);
		index.Load(GL_ELEMENT_ARRAY_BUFFER, nf, face);
	}
	GLuint GetBuffer()const{
		return index.GetBuffer();
	}
	//�O�p�`�̐������o��
	GLuint GetNum() const{
		return index.GetNum();
	}
	void Draw(GLint first = 0, GLsizei count = 0) const{
		//���_�z��I�u�W�F�N�g�̎w��
		Use();

		//�`��
		glDrawElements(GL_TRIANGLES, (count > 0 ? count : GetNum() - first) * 3, GL_UNSIGNED_INT,
			static_cast<GLuint(*)[3]>(0) + first);
	}
};

