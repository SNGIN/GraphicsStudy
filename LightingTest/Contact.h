#pragma once
#include "PhysicsMathBase.h"
#include "Constraint.h"

#define NUM_CONTACT 4

//�Փ˓_
struct ContactPoint
{
	float distance;//�ђʐ[�x
	Vector3 pointA;//����A�̃��[�J�����W�ł̏Փ˓_
	Vector3 pointB;//����B�̃��[�J�����W�ł̏Փ˓_
	Vector3 normal;//�Փ˓_�̖@���x�N�g��(���[���h���W)
	Constraint constraints[3];//�S��

	//������
	void reset(){
		constraints[0].accumImpulse = 0.0f;
		constraints[1].accumImpulse = 0.0f;
		constraints[2].accumImpulse = 0.0f;
	}
};

struct Contact
{
	unsigned int m_numContacts;//�Փː�
	float m_friction;//���C
	ContactPoint m_contactPoints[NUM_CONTACT];//�Փ˓_�̔z��
	
	//����Փ˓_�̒T��
	int FindNearestContactPoint(const Vector3 &newPointA, const Vector3 &newPointB, const Vector3 &newNormal);

	//�Փ˓_����ւ�
	int Sort4ContactPoints(const Vector3 &newPoint, float newDistance);

	//�Փ˓_��j������
	void RemoveContactPoint(int i);

	//������
	void Reset();

	//�Փ˓_�����t���b�V������
	void Refresh(const Vector3 &pA, const Quat &qA, const Vector3 &pB, const Quat &qB);

	//�Փ˂̃}�[�W
	void Merge(const Contact &contact);

	//�Փ˓_�̒ǉ�
	void AddContact(float penetrationDepth, const Vector3 &normal, const Vector3 &contactPointA, const Vector3 &contactPointB);

};