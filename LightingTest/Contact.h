#pragma once
#include "PhysicsMathBase.h"
#include "Constraint.h"

#define NUM_CONTACT 4

//衝突点
struct ContactPoint
{
	float distance;//貫通深度
	Vector3 pointA;//剛体Aのローカル座標での衝突点
	Vector3 pointB;//剛体Bのローカル座標での衝突点
	Vector3 normal;//衝突点の法線ベクトル(ワールド座標)
	Constraint constraints[3];//拘束

	//初期化
	void reset(){
		constraints[0].accumImpulse = 0.0f;
		constraints[1].accumImpulse = 0.0f;
		constraints[2].accumImpulse = 0.0f;
	}
};

struct Contact
{
	unsigned int m_numContacts;//衝突数
	float m_friction;//摩擦
	ContactPoint m_contactPoints[NUM_CONTACT];//衝突点の配列
	
	//同一衝突点の探索
	int FindNearestContactPoint(const Vector3 &newPointA, const Vector3 &newPointB, const Vector3 &newNormal);

	//衝突点入れ替え
	int Sort4ContactPoints(const Vector3 &newPoint, float newDistance);

	//衝突点を破棄する
	void RemoveContactPoint(int i);

	//初期化
	void Reset();

	//衝突点をリフレッシュする
	void Refresh(const Vector3 &pA, const Quat &qA, const Vector3 &pB, const Quat &qB);

	//衝突のマージ
	void Merge(const Contact &contact);

	//衝突点の追加
	void AddContact(float penetrationDepth, const Vector3 &normal, const Vector3 &contactPointA, const Vector3 &contactPointB);

};