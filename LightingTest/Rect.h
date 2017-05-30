#pragma once
#include "Commonheader.h"
#include "ShapeObject.h"
#include "Material.h"
#include "Texture.h"

class Rect:public ShapeObject
{
public:
	Rect();
	Rect(GLfloat width, GLfloat height);
	~Rect();

	void SetMaterial(Material *mat);
	ShapeTriangle* mtriangle;

	virtual void Draw();

	GLfloat* GetVertPos();
	GLfloat* GetVertPos(int i);
	GLuint* GetFace();

private:
	Material* mMaterial;

	GLfloat uv[4][2];

	GLfloat m_vertPos[4][3];
	GLuint m_faces[6];

	//uv座標のための頂点配列、バッファオブジェクト
	GLuint vao;
	GLuint vbo;
};