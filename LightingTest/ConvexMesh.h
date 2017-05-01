#pragma once
#include "PhysicsMathBase.h"

#define CONVEX_MESH_MAX_VERTICES	34
#define CONVEX_MESH_MAX_EDGES		96
#define CONVEX_MESH_MAX_FACETS		64

/// エッジの種類
enum EdgeType {
	EdgeTypeConvex,	///< 凸エッジ
	EdgeTypeConcave,	///< 凹エッジ
	EdgeTypeFlat,	///< 平坦エッジ
};

/// エッジ
struct Edge {
	unsigned char type; ///< エッジの種類
	unsigned char vertId[2]; ///< 端点の頂点インデックス
	unsigned char facetId[2]; ///< 共有する面インデックス
};

/// ３角形面
struct Facet {
	unsigned int vertId[3]; ///< 頂点インデックス
	unsigned int edgeId[3]; ///< エッジインデックス
	Vector3 normal; ///< 面法線ベクトル
};

/// 凸メッシュ
struct ConvexMesh {
	unsigned char m_numVertices; ///< 頂点数
	unsigned char m_numFacets; ///< 面数
	unsigned char m_numEdges; ///< エッジ数
	Vector3 m_vertices[CONVEX_MESH_MAX_VERTICES]; ///< 頂点配列
	Edge m_edges[CONVEX_MESH_MAX_EDGES]; ///< エッジ配列
	Facet m_facets[CONVEX_MESH_MAX_FACETS]; ///< 面配列

	/// 初期化
	void reset()
	{
		m_numVertices = 0;
		m_numFacets = 0;
		m_numEdges = 0;
	}
};

/// 軸上に凸メッシュを投影し、最小値と最大値を得る
/// @param[out] pmin 投影領域の最小値
/// @param[out] pmax 投影領域の最大値
/// @param convexMesh 凸メッシュ
/// @param axis 投影軸
void GetProjection(
	float &pmin, float &pmax,
	const ConvexMesh *convexMesh,
	const Vector3 &axis);

/// 凸メッシュを作成する<br>
/// ・入力データが既に凸包になっていること。<br>
/// ・３平面から共有されるエッジ、穴あき面は禁止。<br>
/// ・縮退面は自動的に削除される。
/// @param[out] convexMesh 凸メッシュ
/// @param vertices 頂点配列
/// @param numVertices 頂点数
/// @param indices 面インデックス配列
/// @param numIndices 面インデックス数
/// @param scale スケール
/// @return 凸メッシュの作成に成功した場合はtrueを返す。
bool CreateConvexMesh(ConvexMesh *convexMesh,
	const float *vertices, unsigned int numVertices,
	const unsigned short *indices, unsigned int numIndices,
	const Vector3 &scale);


