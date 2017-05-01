#include "PhysicsMathBase.h"

struct RigidBodyElements{
	Matrix3 m_inertia;	//�����e���\��
	float m_mass;	//����
	float m_restitution;	//�����W��
	float m_friction;	//���C�W��

	void Reset(){
		m_mass = 1.0f;
		m_inertia = Matrix3::identity();
		m_restitution = 0.2f;
		m_friction = 0.6f;
	}
};