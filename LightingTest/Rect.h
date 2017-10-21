#pragma once
#include "Commonheader.h"
#include "ShapeObject.h"
#include "Material.h"
#include "Texture.h"

class Rect:public ShapeObject
{
public:
	Rect();
	Rect(GLfloat width, GLfloat height, Vector3 a_pos,bool a_billboard);
	~Rect();

	void SetMaterial(Material *mat);
	ShapeElements* mtriangle;

	virtual void Draw();

	GLfloat* GetVertPos();
	GLfloat* GetVertPos(int i);
	GLuint* GetFace();

	Vector3 GetPos(){
		return position;
	}

private:
	Material* mMaterial;

	GLfloat uv[6][2];

	GLfloat m_vertPos[4][3];
	GLuint m_faces[6];

	//uv座標のためのバッファオブジェクト
	GLuint vao;

	Vector3 position;
	bool billboard;
};