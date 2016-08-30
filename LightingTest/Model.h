#pragma once
#include "ShapeMesh.h"
#include "Material.h"

class Model
{
	ShapeMesh *m_Mesh;
	// �����ގ������蓖�Ă�|���S���O���[�v��
	GLuint ng;
	// �����ގ������蓖�Ă�|���S���O���[�v�̍ŏ��̃|���S���Ɛ�
	GLuint(*group)[2];
	//�}�e���A��
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