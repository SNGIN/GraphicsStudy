#pragma once
#include "ShapeMesh.h"
#include "Material.h"

class Model
{
	ShapeMesh *m_Mesh;
	// 同じ材質を割り当てるポリゴングループ数
	GLuint ng;
	// 同じ材質を割り当てるポリゴングループの最初のポリゴンと数
	GLuint(*group)[2];
	//マテリアル
	std::vector<Material> m_MaterialList;

	bool FileLoad(const char *name,GLuint &nv, GLfloat (*&pos)[3],GLfloat (*&norm)[3],
		GLuint &nf, GLuint (*&face)[3],bool normalize);

public:
	Model();
	~Model();
	Model(const char *name, bool normalize);

	void Draw();
	void MaterialAdd(Material mat);
};