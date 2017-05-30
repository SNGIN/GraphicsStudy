#pragma once
#include "PhysicsMathBase.h"

#define MAX_LINEAR_VELOCITY		340.0f
#define MAX_ANGULAR_VELOCITY	(EPX_PI * 60.0f)

enum MotionType{
	TypeActive,
	TypeStatic
};

//���̂̏��
struct RigidbodyState{
	Vector3 m_position;	//�ʒu
	Quat m_orientation;	//�p��
	Vector3 m_linearVelocity;	//���i���x
	Vector3 m_angularVelocity;	//��]���x
	MotionType m_motionType;	//�U�镑��

	void Reset(){
		m_position = Vector3(0.0f);
		m_orientation = Quat::identity();
		m_linearVelocity = Vector3(0.0f);
		m_angularVelocity = Vector3(0.0f);
		m_motionType = TypeActive;
	}
};