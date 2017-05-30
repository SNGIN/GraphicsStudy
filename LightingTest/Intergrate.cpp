#include "Physics.h"

#define MAX_LINEAR_VELOCITY		340.0f
#define MAX_ANGULAR_VELOCITY	(PI * 60.0f)

//積分
void Physics::Integrate(RigidbodyState &state, unsigned int numRigidbodys, float timestep){

	Quat dAng = Quat(state.m_angularVelocity, 0)*state.m_orientation*0.5f;

	state.m_position += state.m_linearVelocity * timestep;
	state.m_orientation = normalize(state.m_orientation + dAng*timestep);
}

//外力計算
void Physics::ApplyExternalForce(RigidbodyState &state, const RigidBodyElements &bodyelements, const Vector3 &externalForce, const Vector3 &externalTorque, float timeStep){
	//動かない物体なら外力計算なし
	if (state.m_motionType == MotionType::TypeStatic){
		return;
	}

	//TODO:姿勢計算
	Matrix3 orientation(state.m_orientation);
	Matrix3 worldInertia = orientation * bodyelements.m_inertia * transpose(orientation);
	Matrix3 worldInertiaInv = orientation * inverse(bodyelements.m_inertia) * transpose(orientation);
	Vector3 angularMomentum = worldInertia * state.m_angularVelocity;

	state.m_linearVelocity += externalForce / bodyelements.m_mass * timeStep;
	angularMomentum += externalTorque * timeStep;
	state.m_angularVelocity = worldInertiaInv * angularMomentum;

	//TODO:速度オーバー処理
	float velocitySqrt = lengthSqr(state.m_linearVelocity);
	if (velocitySqrt > (MAX_LINEAR_VELOCITY*MAX_LINEAR_VELOCITY)){
		state.m_linearVelocity = (state.m_linearVelocity / sqrtf(velocitySqrt)) * MAX_LINEAR_VELOCITY;
	}

	//TODO:角速度オーバー処理
	float angleVelocitySqrt = lengthSqr(state.m_angularVelocity);
	if (angleVelocitySqrt > (MAX_ANGULAR_VELOCITY * MAX_ANGULAR_VELOCITY)){
		state.m_angularVelocity = (state.m_angularVelocity / sqrtf(angleVelocitySqrt))*MAX_ANGULAR_VELOCITY;
	}
}