#include "Physics.h"

#define MAX_LINEAR_VELOCITY		340.0f
#define MAX_ANGULAR_VELOCITY	(PI * 60.0f)

//�ϕ�
void Physics::Integrate(RigidbodyState &state, unsigned int numRigidbodys, float timestep){

	Quat dAng = Quat(state.m_angularVelocity, 0)*state.m_orientation*0.5f;

	state.m_position += state.m_linearVelocity * timestep;
	state.m_orientation = normalize(state.m_orientation + dAng*timestep);
}

//�O�͌v�Z
void Physics::ApplyExternalForce(RigidbodyState &state, const RigidBodyElements &bodyelements, const Vector3 &externalForce, const Vector3 &externalTorque, float timeStep){
	//�����Ȃ����̂Ȃ�O�͌v�Z�Ȃ�
	if (state.m_motionType == MotionType::TypeStatic){
		return;
	}

	//TODO:�p���v�Z
	Matrix3 orientation(state.m_orientation);
	Matrix3 worldInertia = orientation * bodyelements.m_inertia * transpose(orientation);
	Matrix3 worldInertiaInv = orientation * inverse(bodyelements.m_inertia) * transpose(orientation);
	Vector3 angularMomentum = worldInertia * state.m_angularVelocity;

	state.m_linearVelocity += externalForce / bodyelements.m_mass * timeStep;
	angularMomentum += externalTorque * timeStep;
	state.m_angularVelocity = worldInertiaInv * angularMomentum;

	//TODO:���x�I�[�o�[����
	float velocitySqrt = lengthSqr(state.m_linearVelocity);
	if (velocitySqrt > (MAX_LINEAR_VELOCITY*MAX_LINEAR_VELOCITY)){
		state.m_linearVelocity = (state.m_linearVelocity / sqrtf(velocitySqrt)) * MAX_LINEAR_VELOCITY;
	}

	//TODO:�p���x�I�[�o�[����
	float angleVelocitySqrt = lengthSqr(state.m_angularVelocity);
	if (angleVelocitySqrt > (MAX_ANGULAR_VELOCITY * MAX_ANGULAR_VELOCITY)){
		state.m_angularVelocity = (state.m_angularVelocity / sqrtf(angleVelocitySqrt))*MAX_ANGULAR_VELOCITY;
	}
}