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

	//uv座標のための頂点配列、バッファオブジェクト
	GLuint vao;
	GLuint vbo;
};