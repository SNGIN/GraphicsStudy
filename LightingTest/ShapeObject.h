#pragma once
#include "ShapeElements.h"
#include "Material.h"
#include "PhysicsInclude.h"

class ShapeObject:public ShapeElements
{
protected:
	//�`��Ɏg�p������(���_�Ƃ����_�C���f�b�N�X�Ƃ�)
	ShapeElements* m_Elements;
	//�}�e���A��
	Material* m_Material;

	//���b�V�����(TODO:�R���X�g���N�^�Ń��b�V���f�[�^�̓o�^)

public:
	ShapeObject();
	~ShapeObject();

	void MaterialSet(Material* mat);

	Material* GetMaterial(){
		//std::cout << m_Material << std::endl;
		return m_Material;
	}

};

