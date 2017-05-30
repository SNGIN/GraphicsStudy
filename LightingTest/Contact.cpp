#pragma once
#include "Contact.h"

#define CONTACT_SAME_POINT			0.01f
#define CONTACT_THRESHOLD_NORMAL	0.01f	// �Փ˓_��臒l�i�@�������j
#define CONTACT_THRESHOLD_TANGENT	0.002f	// �Փ˓_��臒l�i���ʏ�j

static inline
float CalcArea4Points(const Vector3 &p0, const Vector3 &p1, const Vector3 &p2, const Vector3 &p3){
	float areaSqrtA = lengthSqr(cross(p0 - p1, p2 - p3));
	float areaSqrtB = lengthSqr(cross(p0 - p2, p1 - p3));
	float areaSqrtC = lengthSqr(cross(p0 - p3, p1 - p2));
	return MAX(MAX(areaSqrtA, areaSqrtB), areaSqrtC);
}

//����Փ˓_�̒T��
//�����Փ˓_���������炻�̃C���f�b�N�X��Ԃ��A�݂���Ȃ����-1
int Contact::FindNearestContactPoint(const Vector3 &newPointA, const Vector3 &newPointB, const Vector3 &newNormal){
	int nearestIdx = -1;

	float minDiff = CONTACT_SAME_POINT;
	for (unsigned i = 0; i < m_numContacts; i++){
		float diffA = lengthSqr(m_contactPoints[i].pointA - newPointA);
		float diffB = lengthSqr(m_contactPoints[i].pointB - newPointB);
		if (diffA < minDiff && diffB < minDiff && dot(newNormal, m_contactPoints[i].normal) > 0.99f){
			minDiff = MAX(diffA, diffB);
			nearestIdx = i;
		}
	}

	return nearestIdx;
}

/// �Փ˓_�����ւ���
/// @return �j������Փ˓_�̃C���f�b�N�X��Ԃ��B
int Contact::Sort4ContactPoints(const Vector3 &newPoint, float newDistance){
	int maxPenetrationIndex = -1;
	float maxPenetration = newDistance;

	for (unsigned i = 0; i < m_numContacts; i++){
		if (m_contactPoints[i].distance < maxPenetration){
			maxPenetrationIndex = i;
			maxPenetration = m_contactPoints[i].distance;
		}
	}

	float res[4] = { 0.0f };

	//�e�_�����������̏Փ˓_�����ʐς̂����A�����Ƃ��傫�����̂�I��
	//p124(Tree)

	Vector3 newp(newPoint);
	Vector3 p[4] = {
		m_contactPoints[0].pointA,
		m_contactPoints[1].pointA,
		m_contactPoints[2].pointA,
		m_contactPoints[3].pointA,
	};

	if (maxPenetrationIndex != 0){
		res[0] = CalcArea4Points(newp, p[1], p[2], p[3]);
	}

	if (maxPenetrationIndex != 1) {
		res[1] = CalcArea4Points(newp, p[0], p[2], p[3]);
	}

	if (maxPenetrationIndex != 2) {
		res[2] = CalcArea4Points(newp, p[0], p[1], p[3]);
	}

	if (maxPenetrationIndex != 3) {
		res[3] = CalcArea4Points(newp, p[0], p[1], p[2]);
	}

	int maxIndex = 0;
	float maxValue = res[0];

	if (res[1] > maxValue){
		maxIndex = 1;
		maxValue = res[1];
	}

	if (res[2] > maxValue){
		maxIndex = 2;
		maxValue = res[2];
	}

	if (res[3] > maxValue){
		maxIndex = 3;
		maxValue = res[3];
	}

	return maxIndex;
}

//������
void Contact::Reset(){
	m_numContacts = 0;
	for (int i = 0; i < NUM_CONTACT; i++){
		m_contactPoints[i].reset();
	}
}

// �Փ˓_��j������
// �����͔j������Փ˓_�̃C���f�b�N�X
void Contact::RemoveContactPoint(int i){
	m_contactPoints[i] = m_contactPoints[m_numContacts - 1];
	m_numContacts--;
}

// �Փ˓_�����t���b�V��
void Contact::Refresh(const Vector3 &pA, const Quat &qA, const Vector3 &pB, const Quat &qB){
	//�Փ˓_�X�V
	//�Փ˓_�Ԃ̋�����臒l�𒴂��������
	for (int i = 0; i < (int)m_numContacts; i++){
		Vector3 normal = m_contactPoints[i].normal;
		Vector3 cpA = pA + rotate(qA, m_contactPoints[i].pointA);
		Vector3 cpB = pB + rotate(qB, m_contactPoints[i].pointB);

		// �ђʐ[�x���v���X�ɓ]�������ǂ������`�F�b�N
		float distance = dot(normal, cpA - cpB);
		if (distance > CONTACT_THRESHOLD_NORMAL) {
			RemoveContactPoint(i);
			i--;
			continue;
		}
		m_contactPoints[i].distance = distance;

		// �[�x�������������ė��_�̋������`�F�b�N
		cpA = cpA - m_contactPoints[i].distance * normal;
		float distanceAB = lengthSqr(cpA - cpB);
		if (distanceAB > CONTACT_THRESHOLD_TANGENT) {
			RemoveContactPoint(i);
			i--;
			continue;
		}
	}
}

//�Փ˓_�̃}�[�W
void Contact::Merge(const Contact &contact){
	for (unsigned int i = 0; i < contact.m_numContacts; i++){
		ContactPoint &cp = m_contactPoints[i];

		int id = FindNearestContactPoint(cp.pointA, cp.pointB, cp.normal);

		if (id >= 0) {
			if (fabs(dot(cp.normal, m_contactPoints[id].normal)) > 0.99f) {
				// ����_�𔭌��A�~�ς��ꂽ���������p��
				m_contactPoints[id].distance = cp.distance;
				m_contactPoints[id].pointA = cp.pointA;
				m_contactPoints[id].pointB = cp.pointB;
				m_contactPoints[id].normal = cp.normal;
			}
			else {
				// ����_�ł͂��邪�@�����Ⴄ���ߍX�V
				m_contactPoints[id] = cp;
			}
		}
		else if (m_numContacts < NUM_CONTACT) {
			// �Փ˓_��V�K�ǉ�
			m_contactPoints[m_numContacts++] = cp;
		}
		else {
			// �\�[�g
			id = Sort4ContactPoints(cp.pointA, cp.distance);

			// �R���^�N�g�|�C���g����ւ�
			m_contactPoints[id] = cp;
		}
	}
}

// �Փ˓_��ǉ�����
void Contact::AddContact(
	float penetrationDepth,
	const Vector3 &normal,
	const Vector3 &contactPointA,
	const Vector3 &contactPointB)
{
	int id = FindNearestContactPoint(contactPointA, contactPointB, normal);

	if (id < 0 && m_numContacts < NUM_CONTACT) {
		// �Փ˓_��V�K�ǉ�
		id = m_numContacts++;
		m_contactPoints[id].reset();
	}
	else if (id < 0){
		id = Sort4ContactPoints(contactPointA, penetrationDepth);
		m_contactPoints[id].reset();
	}

	m_contactPoints[id].distance = penetrationDepth;
	m_contactPoints[id].pointA = contactPointA;
	m_contactPoints[id].pointB = contactPointB;
	m_contactPoints[id].normal = normal;
}



