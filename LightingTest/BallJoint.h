#pragma once
#include "PhysicsMathBase.h"
#include "Constraint.h"

/// ボールジョイント
struct BallJoint {
	float bias; ///< 拘束の強さの調整値
	unsigned int rigidBodyA; ///< 剛体Aへのインデックス
	unsigned int rigidBodyB; ///< 剛体Bへのインデックス
	Vector3 anchorA; ///< 剛体Aのローカル座標系における接続点
	Vector3 anchorB; ///< 剛体Bのローカル座標系における接続点
	Constraint constraint; ///< 拘束

	/// 初期化
	void Reset()
	{
		bias = 0.1f;
		constraint.accumImpulse = 0.0f;
	}
};
