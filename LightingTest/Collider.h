#pragma once
#include "PhysicsShape.h"

#define NUM_SHAPES 5

/// �`��R���e�i
struct Collider {
	unsigned char m_numShapes; ///< �ێ�����`��
	PhysicsShape m_shapes[NUM_SHAPES]; ///< �`��̔z��
	Vector3 m_center; ///< AABB�̒��S
	Vector3 m_half; ///< AABB�̃T�C�Y�̔���

	/// ������
	void reset()
	{
		m_numShapes = 0;
		m_center = Vector3(0.0f);
		m_half = Vector3(0.0f);
	}

	/// �`���o�^����B
	/// �󂫂��Ȃ���Ζ��������
	/// @param shape �`��
	void addShape(const PhysicsShape &shape)
	{
		if (m_numShapes < NUM_SHAPES) {
			m_shapes[m_numShapes++] = shape;
		}
	}

	/// �`��o�^�̊�����ʒm����B
	/// �S�Ă̌`���o�^������ɌĂяo���A�S�̂��͂�AABB���쐬����B
	void finish()
	{
		// AABB���v�Z����
		Vector3 aabbMax(-FLT_MAX), aabbMin(FLT_MAX);
		for (unsigned int i = 0; i<m_numShapes; i++) {
			const ConvexMesh &mesh = m_shapes[i].m_geometry;

			for (unsigned int v = 0; v<mesh.m_numVertices; v++) {
				aabbMax = maxPerElem(aabbMax, m_shapes[i].m_offsetPosition + rotate(m_shapes[i].m_offsetOrientation, mesh.m_vertices[v]));
				aabbMin = minPerElem(aabbMin, m_shapes[i].m_offsetPosition + rotate(m_shapes[i].m_offsetOrientation, mesh.m_vertices[v]));
			}
		}
		m_center = (aabbMax + aabbMin) * 0.5f;
		m_half = (aabbMax - aabbMin) * 0.5f;
	}
};
