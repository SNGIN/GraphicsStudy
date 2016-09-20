#pragma once
#include "Commonheader.h"
#include "Buffer.h"

//頂点情報を持つクラス
class ShapePoints
{
	//頂点配列オブジェクト
	GLuint vao;
	GLenum mode;

	//頂点バッファオブジェクト
	Buffer<GLfloat[3]> position;
	
	//頂点位置の確保
	void LoadPosition(GLuint nv, const GLfloat(*pos)[3], GLenum usage){
		// 頂点位置
		position.Load(GL_ARRAY_BUFFER, nv, pos, usage);
		// このバッファオブジェクトは index == 0 の in 変数から入力する
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

	//コピーコンストラクタ.
	ShapePoints(const ShapePoints &o)
		: vao(o.vao), mode(o.mode)
	{
		glBindVertexArray(vao);
	}

	//代入演算子
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
	//! \brief ポイントの描画.
	virtual void draw(GLint first = 0, GLsizei count = 0) const{
		// 頂点配列オブジェクトを指定する
		Use();

		// 図形を描画する
		glDrawArrays(this->mode, first, count > 0 ? count : pnum() - first);
	}
};

