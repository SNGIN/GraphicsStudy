#include "PhysicsMathBase.h"

struct RigidBodyElements{
	Matrix3 m_inertia;	//Šµ«ƒeƒ“ƒ\ƒ‹
	float m_mass;	//¿—Ê
	float m_restitution;	//”½”­ŒW”
	float m_friction;	//–€CŒW”

	void Reset(){
		m_mass = 1.0f;
		m_inertia = Matrix3::identity();
		m_restitution = 0.2f;
		m_friction = 0.6f;
	}
};