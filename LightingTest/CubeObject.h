#pragma once
#include "ShapeObject.h"

// サイズ1x1x1のボックス
const int box_numVertices = 8;
const int box_numIndices = 36;
const float box_vertices[] = {
	-1.000000, -1.000000, 1.000000, 1.000000, -1.000000, 1.000000, -1.000000, 1.000000, 1.000000, 1.000000, 1.000000, 1.000000, -1.000000, 1.000000, -1.000000, 1.000000, 1.000000, -1.000000, -1.000000, -1.000000, -1.000000, 1.000000, -1.000000, -1.000000
};
const unsigned short box_indices[] = {
	0, 1, 2, 2, 1, 3, 2, 3, 4, 4, 3, 5, 4, 5, 6, 6, 5, 7, 6, 7, 0, 0, 7, 1, 1, 7, 3, 3, 7, 5, 6, 0, 4, 4, 0, 2
};

class CubeObject :public ShapeObject
{
	private:
		GLfloat pv[8][3];
		GLfloat nv[8][3];
		GLfloat tv[8][2];
		GLuint face[36][3];
	public:
		CubeObject();
		CubeObject(Vector3 scale);
		~CubeObject();
		void Draw();
		GLfloat* GetVertices();
		GLfloat GetNumvertices();
		GLuint* GetFaces();
		GLuint GetNumFaces();
};

