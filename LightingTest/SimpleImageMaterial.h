#pragma once
#include "Material.h"

class SimpleImageMaterial:public Material
{
	Texture* mtex;
	GLuint texLoc;
	GLuint uvLoc;

	GLuint vao;
	GLuint vbo;
public:
	SimpleImageMaterial(Shader* shader, Texture* tex);
	~SimpleImageMaterial();

	void UseTexture();
	void SetTexLoc();
	void OffTexture();

	Texture* GetTex(){
		return mtex;
	}
};

