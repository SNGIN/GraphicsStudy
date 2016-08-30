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

	//コピーコンストラクタ
	ShapeMesh(const ShapeMesh &o) :
		ShapeTriangle(o), index(o.index){}

	ShapeMesh &operator=(const ShapeMesh &o){
		if (&o != this){
			ShapeTriangle::operator=(o);
			index = o.index;
		}
		return *this;
	}

	//メンバー変数のゲッター
	GLuint Pos(){

	}

	//バッファオブジェクトに頂点のインデックスデータを転送
	//! \brief 既存のバッファオブジェクトに頂点の位置データと法線データを転送する.
	//!   \param nv 転送する頂点の位置データの数 (0 ならバッファ全体).
	//!   \param pos 転送元の頂点の位置データが格納されてている領域の先頭のポインタ.
	//!   \param norm 転送元の頂点の法線データが格納されてている領域の先頭のポインタ.
	//!   \param offset 転送先のバッファオブジェクトの先頭の要素番号.
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
	//三角形の数を取り出す
	GLuint GetNum() const{
		return index.GetNum();
	}
	void Draw(GLint first = 0, GLsizei count = 0) const{
		//頂点配列オブジェクトの指定
		Use();

		//描画
		glDrawElements(GL_TRIANGLES, (count > 0 ? count : GetNum() - first) * 3, GL_UNSIGNED_INT,
			static_cast<GLuint(*)[3]>(0) + first);
	}
};

