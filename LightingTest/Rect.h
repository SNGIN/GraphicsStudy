#pragma once
#include "Commonheader.h"
#include "ShapeTriangle.h"
#include "Material.h"
#include "Texture.h"

class Rect
{
public:
	Rect();
	Rect(GLfloat width, GLfloat height);
	~Rect();

	void SetMaterial(Material *mat);

	void Draw();

private:
	ShapeTriangle* mtriangle;
	Material* mMaterial;

	GLfloat uv[4][2];

	//uv���W�̂��߂̒��_�z��A�o�b�t�@�I�u�W�F�N�g
	GLuint vao;
	GLuint vbo;
};