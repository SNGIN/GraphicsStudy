#pragma once
#include "PhysicsMathBase.h"

#define CONVEX_MESH_MAX_VERTICES	34
#define CONVEX_MESH_MAX_EDGES		96
#define CONVEX_MESH_MAX_FACETS		64

/// �G�b�W�̎��
enum EdgeType {
	EdgeTypeConvex,	///< �ʃG�b�W
	EdgeTypeConcave,	///< ���G�b�W
	EdgeTypeFlat,	///< ���R�G�b�W
};

/// �G�b�W
struct Edge {
	unsigned char type; ///< �G�b�W�̎��
	unsigned char vertId[2]; ///< �[�_�̒��_�C���f�b�N�X
	unsigned char facetId[2]; ///< ���L����ʃC���f�b�N�X
};

/// �R�p�`��
struct Facet {
	unsigned int vertId[3]; ///< ���_�C���f�b�N�X
	unsigned int edgeId[3]; ///< �G�b�W�C���f�b�N�X
	Vector3 normal; ///< �ʖ@���x�N�g��
};

/// �ʃ��b�V��
struct ConvexMesh {
	unsigned char m_numVertices; ///< ���_��
	unsigned char m_numFacets; ///< �ʐ�
	unsigned char m_numEdges; ///< �G�b�W��
	Vector3 m_vertices[CONVEX_MESH_MAX_VERTICES]; ///< ���_�z��
	Edge m_edges[CONVEX_MESH_MAX_EDGES]; ///< �G�b�W�z��
	Facet m_facets[CONVEX_MESH_MAX_FACETS]; ///< �ʔz��

	/// ������
	void reset()
	{
		m_numVertices = 0;
		m_numFacets = 0;
		m_numEdges = 0;
	}
};

/// ����ɓʃ��b�V���𓊉e���A�ŏ��l�ƍő�l�𓾂�
/// @param[out] pmin ���e�̈�̍ŏ��l
/// @param[out] pmax ���e�̈�̍ő�l
/// @param convexMesh �ʃ��b�V��
/// @param axis ���e��
void GetProjection(
	float &pmin, float &pmax,
	const ConvexMesh *convexMesh,
	const Vector3 &axis);

/// �ʃ��b�V�����쐬����<br>
/// �E���̓f�[�^�����ɓʕ�ɂȂ��Ă��邱�ƁB<br>
/// �E�R���ʂ��狤�L�����G�b�W�A�������ʂ͋֎~�B<br>
/// �E�k�ޖʂ͎����I�ɍ폜�����B
/// @param[out] convexMesh �ʃ��b�V��
/// @param vertices ���_�z��
/// @param numVertices ���_��
/// @param indices �ʃC���f�b�N�X�z��
/// @param numIndices �ʃC���f�b�N�X��
/// @param scale �X�P�[��
/// @return �ʃ��b�V���̍쐬�ɐ��������ꍇ��true��Ԃ��B
bool CreateConvexMesh(ConvexMesh *convexMesh,
	const float *vertices, unsigned int numVertices,
	const unsigned short *indices, unsigned int numIndices,
	const Vector3 &scale);


