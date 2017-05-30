#pragma once
#include "PhysicsMathBase.h"

/// ソルバーボディ
struct SolverBody {
	Vector3 deltaLinearVelocity; ///< 並進速度差分
	Vector3 deltaAngularVelocity; ///< 回転速度差分
	Quat    orientation; ///< 姿勢
	Matrix3 inertiaInv; ///< 慣性テンソルの逆行列
	float   massInv; ///< 質量の逆数
};