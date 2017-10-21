#pragma once
#include "ShapeElements.h"
#include "Material.h"
#include "PhysicsInclude.h"

//�`��n�̃I�u�W�F�N�g�̊��N���X
class ShapeObject
{
protected:
	//�`��Ɏg�p������
	ShapeElements* m_Elements;
	//�}�e���A��
	Material* m_Material;

	GLfloat* vertPosition;
	GLfloat* verticesNormal;
	GLfloat* vertTex;
	GLuint* face;

	GLuint numVert;
	GLuint numFaces;

	Vector3 scale;

public:
	ShapeObject(){};
	ShapeObject(GLuint VertNum, GLuint FaceNum,Vector3 Scale);
	~ShapeObject();

	void MaterialSet(Material* mat);

	Material* GetMaterial(){
		//std::cout << m_Material << std::endl;
		return m_Material;

	}

	void Draw();
	GLfloat* GetVertices();
	GLfloat GetNumvertices();
	GLuint* GetFaces();
	GLuint GetNumFaces();
	Vector3 GetScale();
};

