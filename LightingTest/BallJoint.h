#pragma once
#include "PhysicsMathBase.h"
#include "Constraint.h"

/// �{�[���W���C���g
struct BallJoint {
	float bias; ///< �S���̋����̒����l
	unsigned int rigidBodyA; ///< ����A�ւ̃C���f�b�N�X
	unsigned int rigidBodyB; ///< ����B�ւ̃C���f�b�N�X
	Vector3 anchorA; ///< ����A�̃��[�J�����W�n�ɂ�����ڑ��_
	Vector3 anchorB; ///< ����B�̃��[�J�����W�n�ɂ�����ڑ��_
	Constraint constraint; ///< �S��

	/// ������
	void Reset()
	{
		bias = 0.1f;
		constraint.accumImpulse = 0.0f;
	}
};
