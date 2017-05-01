#pragma once
#include "PhysicsInclude.h"

class Physics
{
public:
	Physics();
	~Physics();

	//シミュレーション系
	bool PhysicsInit();
	void PhysicsRelease();
	void PhysicsUpdate();
	//オブジェクト作成
	void CreateRigidBody(float* vertices, float numvertices, 
		unsigned short* indices, unsigned int numIndices, 
		Vector3 scale = Vector3(1.0f,1.0f,1.0f), MotionType type = MotionType::TypeActive,
		Vector3 pos = Vector3(0), float mass = 1.0f, bool sphere = false);

	//現在の物理シミュレーションのシーンを取得
	const char *PhysicsGetSceneTitle(int i);

	//剛体情報の取得
	int GetNumRigidbodies();
	const RigidbodyState &GetRigidBodyState(int i);
	const RigidBodyElements &GetRigidBodyElements(int i);
	const Collider &GetCollider(int i);

	//衝突情報の取得
};

