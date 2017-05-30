#pragma once
#include "Contact.h"

#define CONTACT_SAME_POINT			0.01f
#define CONTACT_THRESHOLD_NORMAL	0.01f	// 衝突点の閾値（法線方向）
#define CONTACT_THRESHOLD_TANGENT	0.002f	// 衝突点の閾値（平面上）

static inline
float CalcArea4Points(const Vector3 &p0, const Vector3 &p1, const Vector3 &p2, const Vector3 &p3){
	float areaSqrtA = lengthSqr(cross(p0 - p1, p2 - p3));
	float areaSqrtB = lengthSqr(cross(p0 - p2, p1 - p3));
	float areaSqrtC = lengthSqr(cross(p0 - p3, p1 - p2));
	return MAX(MAX(areaSqrtA, areaSqrtB), areaSqrtC);
}

//同一衝突点の探索
//同じ衝突点を見つけたらそのインデックスを返す、みつからなければ-1
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

/// 衝突点を入れ替える
/// @return 破棄する衝突点のインデックスを返す。
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

	//各点を除いた時の衝突点が作る面積のうち、もっとも大きいものを選択
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

//初期化
void Contact::Reset(){
	m_numContacts = 0;
	for (int i = 0; i < NUM_CONTACT; i++){
		m_contactPoints[i].reset();
	}
}

// 衝突点を破棄する
// 引数は破棄する衝突点のインデックス
void Contact::RemoveContactPoint(int i){
	m_contactPoints[i] = m_contactPoints[m_numContacts - 1];
	m_numContacts--;
}

// 衝突点をリフレッシュ
void Contact::Refresh(const Vector3 &pA, const Quat &qA, const Vector3 &pB, const Quat &qB){
	//衝突点更新
	//衝突点間の距離が閾値を超えたら消去
	for (int i = 0; i < (int)m_numContacts; i++){
		Vector3 normal = m_contactPoints[i].normal;
		Vector3 cpA = pA + rotate(qA, m_contactPoints[i].pointA);
		Vector3 cpB = pB + rotate(qB, m_contactPoints[i].pointB);

		// 貫通深度がプラスに転じたかどうかをチェック
		float distance = dot(normal, cpA - cpB);
		if (distance > CONTACT_THRESHOLD_NORMAL) {
			RemoveContactPoint(i);
			i--;
			continue;
		}
		m_contactPoints[i].distance = distance;

		// 深度方向を除去して両点の距離をチェック
		cpA = cpA - m_contactPoints[i].distance * normal;
		float distanceAB = lengthSqr(cpA - cpB);
		if (distanceAB > CONTACT_THRESHOLD_TANGENT) {
			RemoveContactPoint(i);
			i--;
			continue;
		}
	}
}

//衝突点のマージ
void Contact::Merge(const Contact &contact){
	for (unsigned int i = 0; i < contact.m_numContacts; i++){
		ContactPoint &cp = m_contactPoints[i];

		int id = FindNearestContactPoint(cp.pointA, cp.pointB, cp.normal);

		if (id >= 0) {
			if (fabs(dot(cp.normal, m_contactPoints[id].normal)) > 0.99f) {
				// 同一点を発見、蓄積された情報を引き継ぐ
				m_contactPoints[id].distance = cp.distance;
				m_contactPoints[id].pointA = cp.pointA;
				m_contactPoints[id].pointB = cp.pointB;
				m_contactPoints[id].normal = cp.normal;
			}
			else {
				// 同一点ではあるが法線が違うため更新
				m_contactPoints[id] = cp;
			}
		}
		else if (m_numContacts < NUM_CONTACT) {
			// 衝突点を新規追加
			m_contactPoints[m_numContacts++] = cp;
		}
		else {
			// ソート
			id = Sort4ContactPoints(cp.pointA, cp.distance);

			// コンタクトポイント入れ替え
			m_contactPoints[id] = cp;
		}
	}
}

// 衝突点を追加する
void Contact::AddContact(
	float penetrationDepth,
	const Vector3 &normal,
	const Vector3 &contactPointA,
	const Vector3 &contactPointB)
{
	int id = FindNearestContactPoint(contactPointA, contactPointB, normal);

	if (id < 0 && m_numContacts < NUM_CONTACT) {
		// 衝突点を新規追加
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



