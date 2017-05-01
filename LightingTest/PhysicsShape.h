#pragma once
#include "ConvexMesh.h"

struct  PhysicsShape
{
	ConvexMesh m_geometry;	//�ʃ��b�V��
	Vector3 m_offsetPosition;	//�I�t�Z�b�g�ʒu
	Quat m_offsetOrientation;	//�p��

	//������
	void reset(){
		m_geometry.reset();
		m_offsetPosition = Vector3(0.0f);
		m_offsetOrientation = Quat::identity();
	}
};