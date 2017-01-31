#pragma once
#include "Commonheader.h" 
#include "ShapePoints.h"

//頂点クラスを継承して面情報を管理するクラス
class ShapeTriangle:public ShapePoints
{
	//頂点の法線ベクトル
	Buffer<GLfloat[3]> normal;

	void LoadNormal(GLuint nv, const GLfloat(*norm)[3], GLenum usage){
		//頂点法線の設定
		normal.Load(GL_ARRAY_BUFFER, nv, norm, usage);

		//indexの設定
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);
	}

public:

	ShapeTriangle(GLenum mode = GL_TRIANGLES) :ShapePoints(mode){}
	ShapeTriangle(GLuint nv, const GLfloat(*pos)[3], const GLfloat(*norm)[3], GLenum mode = GL_TRIANGLES, GLenum usage = GL_STATIC_DRAW)
		:ShapePoints(nv, pos, mode, usage){
		LoadNormal(nv, norm, usage);
	}

	//コピーコンストラクタ
	ShapeTriangle(const ShapeTriangle &o) : ShapePoints(o), normal(o.normal){}
	
	//代入演算子
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

