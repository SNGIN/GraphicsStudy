#pragma once
#include "Commonheader.h"
#include "BufferBase.h"

class Texture:BufferBase
{
public:
	Texture();
	Texture(GLuint tex);
	Texture(GLsizei width, GLsizei height, GLenum internal, GLenum format, const GLubyte *image);
	Texture(char *name, GLenum internal);
	Texture(const Texture &o):BufferBase(o), texture(o.texture){};

	Texture &operator=(const Texture &o){
		if (&o != this){
			BufferBase::operator=(o);
			texture = o.texture;
		}
		return *this;
	}
	
	void Use(GLuint loc,GLuint unit)const;
	void Release()const;
	GLuint Get()const;
	GLuint LoadTexture(GLsizei width, GLsizei height, GLenum internal, GLenum format, const GLubyte *image);
	GLuint LoadImage(const char *name, GLenum internal);
	GLubyte* LoadTGA(const char *name, GLsizei *width, GLsizei *height, GLenum *format);

	virtual ~Texture();
private:
	GLuint texture;
};

