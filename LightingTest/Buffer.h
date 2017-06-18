#pragma once

#include "Commonheader.h"
#include "BufferBase.h"

//�������Ɋi�[�����o�b�t�@�I�u�W�F�N�g�̃e���v��-�g�N���X
template <typename T>
class Buffer:public BufferBase
{
	//�o�b�t�@�I�u�W�F�N�g
	GLuint buffer;
	//�^�[�Q�b�g
	GLenum target;
	//�f�[�^��
	GLuint number;

public:
	//�f�t�H���g�R���X�g���N�^
	Buffer<T>():number(0){
		glGenBuffers(1, &buffer);
	}
	//��������̃R���X�g���N�^
	Buffer<T>(GLenum target, GLuint number, const T *data, GLenum usage = GL_STATIC_DRAW){
		glGenBuffers(1, &buffer);
		load(target, number, data, usage);
	}

	//! \brief �R�s�[�R���X�g���N�^.
	Buffer<T>(const Buffer<T> &o)
		: BufferBase(o), buffer(o.buffer), target(o.target), number(o.number) {}

	// ���
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
		// �Q�Ƃ��Ă���I�u�W�F�N�g��������Ȃ�o�b�t�@���폜����
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

	//�o�b�t�@�I�u�W�F�N�g�̌��т�(�C���f�b�N�X�o�b�t�@�A���_�o�b�t�@)
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

