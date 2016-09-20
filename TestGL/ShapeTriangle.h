#pragma once
#include "Commonheader.h" 
#include "ShapePoints.h"

class ShapeTriangle:ShapePoints
{
	//���_�z��I�u�W�F�N�g
	GLuint vao;
	//���_�̖@���x�N�g��
	Buffer<GLfloat[3]> normal;

	void LoadNormal(GLuint nv, const GLfloat(*norm)[3], GLenum usage){
		//���_�@���̐ݒ�
		normal.Load(GL_ARRAY_BUFFER, nv, norm, usage);

		//index�̐ݒ�
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);
	}

public:
	ShapeTriangle(){
	}
	ShapeTriangle(GLuint nv,const GLfloat (*pos)[3],const GLfloat (*norm)[3],GLenum usage = GL_STATIC_DRAW)
		:ShapePoints(nv,norm,usage){
		LoadNormal(nv, norm, usage);
	}

	//�R�s�[�R���X�g���N�^
	ShapeTriangle(const ShapeTriangle &o) : ShapePoints(o), normal(o.normal){}
	
	//������Z�q
	ShapeTriangle &operator=(const ShapeTriangle &o){
		if (this != &o){
			ShapePoints::operator=(o);
			normal = o.normal;
		}
		return *this;
	}

	virtual ~ShapeTriangle(){
	}

	void Send(GLuint nv, const GLfloat(*pos)[3], const GLfloat(*norm)[3], GLuint offset = 0){
		ShapePoints::Send(nv, pos, offset);
		normal.Send(nv, norm, offset);
	}
	void Load(GLuint nv, const GLfloat(*pos)[3], const GLfloat(*norm)[3], GLenum usage = GL_STATIC_DRAW){
		ShapePoints::Load(nv, pos, usage);
		LoadNormal(nv, norm, usage);
	}
	GLuint GetNormalBuf() const{
		return normal.GetBuffer();
	}
	GLuint GetNormalNum()const{
		return normal.GetNum();
	}
};
