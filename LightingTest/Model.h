#pragma once
#include "ShapeElements.h"
#include "Material.h"

class Model
{
	ShapeElements* m_Elements;
	//ƒ}ƒeƒŠƒAƒ‹
	Material* m_Material;

	bool FileLoad(const char *name,GLuint &nv, GLfloat (*&pos)[3],GLfloat (*&norm)[3],
		GLuint &nf, GLuint (*&face)[3],bool normalize);

public:
	Model();
	~Model();
	Model(const char *name, bool normalize = false);

	void Draw();
	void MaterialSet(Material* mat);

	Material* GetMaterial(){
		//std::cout << m_Material << std::endl;
		return m_Material;
	}
};