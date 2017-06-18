#pragma once

#include "Commonheader.h"
#include "BufferBase.h"

//メモリに格納されるバッファオブジェクトのテンプレ-トクラス
template <typename T>
class Buffer:public BufferBase
{
	//バッファオブジェクト
	GLuint buffer;
	//ターゲット
	GLenum target;
	//データ数
	GLuint number;

public:
	//デフォルトコンストラクタ
	Buffer<T>():number(0){
		glGenBuffers(1, &buffer);
	}
	//引数ありのコンストラクタ
	Buffer<T>(GLenum target, GLuint number, const T *data, GLenum usage = GL_STATIC_DRAW){
		glGenBuffers(1, &buffer);
		load(target, number, data, usage);
	}

	//! \brief コピーコンストラクタ.
	Buffer<T>(const Buffer<T> &o)
		: BufferBase(o), buffer(o.buffer), target(o.target), number(o.number) {}

	// 代入
	Buffer<T> &operator=(const Buffer<T> &o)
	{
		if (&o != this)
		{
			BufferBase::operator=(o);
			buffer = o.buffer;
			target = o.target;
			number = o.number;
		}
		return *this;
	}

	virtual ~Buffer<T>(){
		// 参照しているオブジェクトが一つだけならバッファを削除する
		if (last())
		{
			glBindBuffer(target, 0);
			glDeleteBuffers(1, &buffer);
		}
	}

	void Send(GLuint number, const T *data, GLuint offset = 0){
		if (number == 0) number = this->number;
		glBufferSubData(target, offset * sizeof (T), number * sizeof (T), data);
	}

	//バッファオブジェクトの結びつけ(インデックスバッファ、頂点バッファ)
	void Load(GLenum target, GLuint number, const T *data, GLenum usage = GL_STATIC_DRAW){
		this->target = target;
		this->number = number;
		glBindBuffer(target, buffer);
		glBufferData(target, number * sizeof (T), data, usage);
	}

	void Copy(GLuint buf){
		glBindBuffer(GL_COPY_READ_BUFFER, buf);
		glBindBuffer(GL_COPY_WRITE_BUFFER, buffer);
		glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, number * sizeof (T));
		glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
		glBindBuffer(GL_COPY_READ_BUFFER, 0);
	}

	GLuint GetBuffer()const{
		return buffer;
	}

	GLuint GetNum()const{
		return number;
	}
};

