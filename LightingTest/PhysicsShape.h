#pragma once
#include "ConvexMesh.h"

struct  PhysicsShape
{
	ConvexMesh m_geometry;	//凸メッシュ
	Vector3 m_offsetPosition;	//オフセット位置
	Quat m_offsetOrientation;	//姿勢

	//初期化
	void reset(){
		m_geometry.reset();
		m_offsetPosition = Vector3(0.0f);
		m_offsetOrientation = Quat::identity();
	}
};