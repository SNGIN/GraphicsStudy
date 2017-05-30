#pragma once
#include "PhysicsMathBase.h"

/// �\���o�[�{�f�B
struct SolverBody {
	Vector3 deltaLinearVelocity; ///< ���i���x����
	Vector3 deltaAngularVelocity; ///< ��]���x����
	Quat    orientation; ///< �p��
	Matrix3 inertiaInv; ///< �����e���\���̋t�s��
	float   massInv; ///< ���ʂ̋t��
};