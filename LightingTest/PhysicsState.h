#pragma once
#include "PhysicsMathBase.h"

#define MAX_LINEAR_VELOCITY		340.0f
#define MAX_ANGULAR_VELOCITY	(EPX_PI * 60.0f)

enum MotionType{
	TypeActive,
	TypeStatic
};

//剛体の状態
struct RigidbodyState{
	Vector3 m_position;	//位置
	Quat m_orientation;	//姿勢
	Vector3 m_linearVelocity;	//併進速度
	Vector3 m_angularVelocity;	//回転速度
	MotionType m_motionType;	//振る舞い

	void Reset(){
		m_position = Vector3(0.0f);
		m_orientation = Quat::identity();
		m_linearVelocity = Vector3(0.0f);
		m_angularVelocity = Vector3(0.0f);
		m_motionType = TypeActive;
	}
};