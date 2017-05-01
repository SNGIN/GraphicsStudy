#include <string.h>
#include "ConvexMesh.h"

//ある軸に投影(軸に投影して、どこかの軸で重なっていなければ衝突していない)
//p147あたり参照
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
	//不正データのチェック
	assert(convexMesh);
	assert(vertices);
	assert(indices);
	assert(dot(scale, scale)>0.0f);

	//最大頂点数を超えたらダメ
	if (numVertices > CONVEX_MESH_MAX_VERTICES || numIndices > CONVEX_MESH_MAX_FACETS * 3) {
		return false;
	}

	//メモリ確保
	memset(convexMesh, 0, sizeof(ConvexMesh));

	// 頂点バッファ作成
	for (unsigned int i = 0; i<numVertices; i++) {
		convexMesh->m_vertices[i][0] = vertices[i * 3];
		convexMesh->m_vertices[i][1] = vertices[i * 3 + 1];
		convexMesh->m_vertices[i][2] = vertices[i * 3 + 2];
		convexMesh->m_vertices[i] = mulPerElem(scale, convexMesh->m_vertices[i]);
	}
	convexMesh->m_numVertices = numVertices;

	// 面バッファ作成
	unsigned int nf = 0;
	for (unsigned int i = 0; i<numIndices / 3; i++) {
		//インデックスから面の3点を決定
		Vector3 p[3] = {
			convexMesh->m_vertices[indices[i * 3]],
			convexMesh->m_vertices[indices[i * 3 + 1]],
			convexMesh->m_vertices[indices[i * 3 + 2]]
		};

		//法線
		Vector3 normal = cross(p[1] - p[0], p[2] - p[0]);
		float areaSqr = lengthSqr(normal); // 面積
		if (areaSqr > EPSILON * EPSILON) {// 縮退面は登録しない
			convexMesh->m_facets[nf].vertId[0] = (unsigned char)indices[i * 3];
			convexMesh->m_facets[nf].vertId[1] = (unsigned char)indices[i * 3 + 1];
			convexMesh->m_facets[nf].vertId[2] = (unsigned char)indices[i * 3 + 2];
			convexMesh->m_facets[nf].normal = normal / sqrtf(areaSqr);
			nf++;
		}
	}
	convexMesh->m_numFacets = nf;

	// エッジバッファ作成(辺に対する面と頂点を登録)
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
				// 初回時は登録のみ
				convexMesh->m_edges[ne].facetId[0] = i;
				convexMesh->m_edges[ne].facetId[1] = i;
				convexMesh->m_edges[ne].vertId[0] = (unsigned char)vertId0;
				convexMesh->m_edges[ne].vertId[1] = (unsigned char)vertId1;
				convexMesh->m_edges[ne].type = EdgeTypeConvex; // 凸エッジで初期化
				facet.edgeId[e] = ne;
				edgeIdTable[tableId] = ne;
				ne++;
				if (ne > CONVEX_MESH_MAX_EDGES) {
					return false;
				}
			}
			else {
				// 共有面を見つけたので、エッジの角度を判定
				assert(edgeIdTable[tableId] < CONVEX_MESH_MAX_EDGES);
				Edge &edge = convexMesh->m_edges[edgeIdTable[tableId]];
				Facet &facetB = convexMesh->m_facets[edge.facetId[0]];

				assert(edge.facetId[0] == edge.facetId[1]);

				// エッジに含まれないＡ面の頂点がB面の表か裏かで判断
				Vector3 s = convexMesh->m_vertices[facet.vertId[(e + 2) % 3]];
				Vector3 q = convexMesh->m_vertices[facetB.vertId[0]];
				float d = dot(s - q, facetB.normal);

				if (d < -EPSILON) {
					edge.type = EdgeTypeConvex;
				}
				else if (d > EPSILON) {
					// 本来ここに来てはいけない
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