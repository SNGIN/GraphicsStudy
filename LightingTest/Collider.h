#pragma once
#include "PhysicsShape.h"

#define NUM_SHAPES 5

/// 形状コンテナ
struct Collider {
	unsigned char m_numShapes; ///< 保持する形状数
	PhysicsShape m_shapes[NUM_SHAPES]; ///< 形状の配列
	Vector3 m_center; ///< AABBの中心
	Vector3 m_half; ///< AABBのサイズの半分

	/// 初期化
	void reset()
	{
		m_numShapes = 0;
		m_center = Vector3(0.0f);
		m_half = Vector3(0.0f);
	}

	/// 形状を登録する。
	/// 空きがなければ無視される
	/// @param shape 形状
	void addShape(const PhysicsShape &shape)
	{
		if (m_numShapes < NUM_SHAPES) {
			m_shapes[m_numShapes++] = shape;
		}
	}

	/// 形状登録の完了を通知する。
	/// 全ての形状を登録した後に呼び出し、全体を囲むAABBを作成する。
	void finish()
	{
		// AABBを計算する
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
