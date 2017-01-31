#pragma once
#include "Commonheader.h"
#include "ShapeMesh.h"

class Model
{
	ShapeMesh *m_Mesh;

	bool FileLoad(const char *name,GLuint &nv, GLfloat (*&pos)[3],GLfloat (*&norm)[3],
		GLuint &nf, GLuint (*&face)[3],bool normalize);

public:
	Model();
	~Model();
	Model(const char *name, bool normalize);

	void Draw();

	/*void LoadObj(const char* filename,
		std::vector<vector4> &vertices,
		std::vector<vector3> &normals,
		std::vector<GLushort> &elements);*/
};