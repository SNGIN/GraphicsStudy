#pragma once
#include "Commonheader.h"
#include "Buffer.h"

//形状の基底クラス
class Shape
{
	//頂点配列オブジェクト
	GLuint vao;
	GLenum mode;

public:

	//! \brief デストラクタ.
	virtual ~Shape()
	{
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &vao);
	}

	//! \brief コンストラクタ.
	//!   \param mode 基本図形の種類.
	Shape(GLenum mode = 0)
	{
		this->mode = mode;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
	}

	//! \brief コピーコンストラクタ.
	Shape(const Shape &o)
		: vao(o.vao), mode(o.mode)
	{
		glBindVertexArray(vao);
	}

	// 代入演算子
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

	//! \brief この図形の頂点配列オブジェクトを指定する.
	void use() const
	{
		glBindVertexArray(vao);
	}

	//! \brief 頂点配列オブジェクト名を取り出す.
	//!   \return 頂点配列オブジェクト名.
	GLuint get() const
	{
		return vao;
	}

	//! \brief 基本図形の設定.
	//!   \param mode 基本図形の種類.
	void setMode(GLenum mode)
	{
		this->mode = mode;
	}

	//! \brief 基本図形の検査.
	//!   \return この頂点配列オブジェクトの基本図形の種類.
	GLenum getMode() const
	{
		return this->mode;
	}

	//! \brief 図形の描画.
	//!   \brief この形状を描画する手続きをオーバーライドする.
	virtual void draw(GLint first = 0, GLsizei count = 0) const = 0;
};

//位置情報を持つ頂点クラス
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

	//コピーコンストラクタ.
	ShapePoints(const ShapePoints &o) :position(o.position), vao(o.vao), mode(o.mode){
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

			position = o.position;
		}
		return *this;
	}
	virtual ~ShapePoints(){
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &vao);
	}

	//! \brief この図形の頂点配列オブジェクトを指定する.
	void Use() const
	{
		glBindVertexArray(vao);
	}

	//! \brief 基本図形の設定.
	//!   \param mode 基本図形の種類.
	void SetMode(GLenum mode)
	{
		this->mode = mode;
	}

	//! \brief 基本図形の検査.
	//!   \return この頂点配列オブジェクトの基本図形の種類.
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

	//! \brief ポイントの描画.
	virtual void Draw(GLint first = 0, GLsizei count = 0) const{
		// 頂点配列オブジェクトを指定する
		Use();

		// 図形を描画する
		glDrawArrays(GetMode(), first, count > 0 ? count : GetPosNum() - first);
	}
};

