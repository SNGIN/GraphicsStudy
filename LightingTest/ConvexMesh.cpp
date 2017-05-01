#include <string.h>
#include "ConvexMesh.h"

//���鎲�ɓ��e(���ɓ��e���āA�ǂ����̎��ŏd�Ȃ��Ă��Ȃ���ΏՓ˂��Ă��Ȃ�)
//p147������Q��
void GetProjection(float &pmin, float &pmax,const ConvexMesh *convexMesh,const Vector3 &axis){
	assert(convexMesh);

	float t_pmin = FLT_MAX;
	float t_pmax = -FLT_MAX;

	for (unsigned int i = 0; i < convexMesh->m_numVertices; i++){
		float proj = dot(axis, convexMesh->m_vertices[i]);
		t_pmin = MIN(t_pmin, proj);
		t_pmax = MAX(t_pmax, proj);
	}
	pmin = t_pmin;
	pmax = t_pmax;
}
bool CreateConvexMesh(ConvexMesh *convexMesh,
	const float *vertices, unsigned int numVertices,
	const unsigned short *indices, unsigned int numIndices,
	const Vector3 &scale = Vector3(1.0f))
{
	//�s���f�[�^�̃`�F�b�N
	assert(convexMesh);
	assert(vertices);
	assert(indices);
	assert(dot(scale, scale)>0.0f);

	//�ő咸�_���𒴂�����_��
	if (numVertices > CONVEX_MESH_MAX_VERTICES || numIndices > CONVEX_MESH_MAX_FACETS * 3) {
		return false;
	}

	//�������m��
	memset(convexMesh, 0, sizeof(ConvexMesh));

	// ���_�o�b�t�@�쐬
	for (unsigned int i = 0; i<numVertices; i++) {
		convexMesh->m_vertices[i][0] = vertices[i * 3];
		convexMesh->m_vertices[i][1] = vertices[i * 3 + 1];
		convexMesh->m_vertices[i][2] = vertices[i * 3 + 2];
		convexMesh->m_vertices[i] = mulPerElem(scale, convexMesh->m_vertices[i]);
	}
	convexMesh->m_numVertices = numVertices;

	// �ʃo�b�t�@�쐬
	unsigned int nf = 0;
	for (unsigned int i = 0; i<numIndices / 3; i++) {
		//�C���f�b�N�X����ʂ�3�_������
		Vector3 p[3] = {
			convexMesh->m_vertices[indices[i * 3]],
			convexMesh->m_vertices[indices[i * 3 + 1]],
			convexMesh->m_vertices[indices[i * 3 + 2]]
		};

		//�@��
		Vector3 normal = cross(p[1] - p[0], p[2] - p[0]);
		float areaSqr = lengthSqr(normal); // �ʐ�
		if (areaSqr > EPSILON * EPSILON) {// �k�ޖʂ͓o�^���Ȃ�
			convexMesh->m_facets[nf].vertId[0] = (unsigned char)indices[i * 3];
			convexMesh->m_facets[nf].vertId[1] = (unsigned char)indices[i * 3 + 1];
			convexMesh->m_facets[nf].vertId[2] = (unsigned char)indices[i * 3 + 2];
			convexMesh->m_facets[nf].normal = normal / sqrtf(areaSqr);
			nf++;
		}
	}
	convexMesh->m_numFacets = nf;

	// �G�b�W�o�b�t�@�쐬(�ӂɑ΂���ʂƒ��_��o�^)
	unsigned char edgeIdTable[CONVEX_MESH_MAX_VERTICES*CONVEX_MESH_MAX_VERTICES / 2];
	memset(edgeIdTable, 0xff, sizeof(edgeIdTable));

	unsigned int ne = 0;
	for (unsigned int i = 0; i < convexMesh -> m_numFacets; i++) {
		Facet &facet = convexMesh->m_facets[i];
		for (unsigned int e = 0; e<3; e++) {
			unsigned int vertId0 = MIN(facet.vertId[e % 3], facet.vertId[(e + 1) % 3]);
			unsigned int vertId1 = MAX(facet.vertId[e % 3], facet.vertId[(e + 1) % 3]);
			unsigned int tableId = vertId1*(vertId1 - 1) / 2 + vertId0;
			if (edgeIdTable[tableId] == 0xff) {
				// ���񎞂͓o�^�̂�
				convexMesh->m_edges[ne].facetId[0] = i;
				convexMesh->m_edges[ne].facetId[1] = i;
				convexMesh->m_edges[ne].vertId[0] = (unsigned char)vertId0;
				convexMesh->m_edges[ne].vertId[1] = (unsigned char)vertId1;
				convexMesh->m_edges[ne].type = EdgeTypeConvex; // �ʃG�b�W�ŏ�����
				facet.edgeId[e] = ne;
				edgeIdTable[tableId] = ne;
				ne++;
				if (ne > CONVEX_MESH_MAX_EDGES) {
					return false;
				}
			}
			else {
				// ���L�ʂ��������̂ŁA�G�b�W�̊p�x�𔻒�
				assert(edgeIdTable[tableId] < CONVEX_MESH_MAX_EDGES);
				Edge &edge = convexMesh->m_edges[edgeIdTable[tableId]];
				Facet &facetB = convexMesh->m_facets[edge.facetId[0]];

				assert(edge.facetId[0] == edge.facetId[1]);

				// �G�b�W�Ɋ܂܂�Ȃ��`�ʂ̒��_��B�ʂ̕\�������Ŕ��f
				Vector3 s = convexMesh->m_vertices[facet.vertId[(e + 2) % 3]];
				Vector3 q = convexMesh->m_vertices[facetB.vertId[0]];
				float d = dot(s - q, facetB.normal);

				if (d < -EPSILON) {
					edge.type = EdgeTypeConvex;
				}
				else if (d > EPSILON) {
					// �{�������ɗ��Ă͂����Ȃ�
					edge.type = EdgeTypeConcave;
				}
				else {
					edge.type = EdgeTypeFlat;
				}

				edge.facetId[1] = i;
			}
		}
	}
	convexMesh->m_numEdges = ne;

	return true;
}