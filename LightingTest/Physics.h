#pragma once
#include "PhysicsInclude.h"

class Physics
{
public:

	Physics();
	~Physics();

	//シミュレーション系
	//bool PhysicsInit();
	void PhysicsRelease();
	void PhysicsUpdate(Vector3 Force, Vector3 Torque);

	//Integrate系=========================
	void Integrate(RigidbodyState &states, unsigned int numRigidbodys, float timestep);
	//====================================

	//Apply系=============================
	void ApplyExternalForce(RigidbodyState &state, const RigidBodyElements &bodyelements, const Vector3 &externalForce, const Vector3 &externalTorque, float timeStep);
	//====================================

	//Broadphase系======================
	bool IntersectAABB(const Vector3 &centerA, const Vector3 &halfA, const Vector3 &centerB, const Vector3 &halfB);
	
	/// ブロードフェーズコールバック<br>
	/// epxBroadPhase()の引数として渡すと、AABB交差判定前に呼ばれる
	/// もどり値のtrueで判定を続行 , falseで判定をキャンセル
	typedef bool(*BroadPhaseCallback)(unsigned int rigidBodyIdA, unsigned int rigidBodyIdB, void *userData);

	//ブロードフェーズ
	void BroadPhase(RigidbodyState* states, Collider* colliders,unsigned int numRigidbodies,
		const Pair *oldPairs,const unsigned int numOldPairs,Pair *newPairs,unsigned int &numNewPairs,const unsigned int maxPairs,
		DefaultAllocator* allocator, void *userData, BroadPhaseCallback callback
		);
	//==================================

	//衝突検出系==========================
	void GetClosestPointTriangle(const Vector3 &point,
		const Vector3 &trianglePoint0,const Vector3 &trianglePoint1,const Vector3 &trianglePoint2,
		const Vector3 &triangleNormal,Vector3 &closestPoint);

	void GetClosestTwoSegments(const Vector3 &segmentPointA0, const Vector3 &segmentPointA1,
		const Vector3 &segmentPointB0, const Vector3 &segmentPointB1,
		Vector3 &closestPointA, Vector3 &closestPointB);

	//
	bool ConvexConvexContact_Local(const ConvexMesh &convexA, const Transform3 &transformA,
		const ConvexMesh &convexB, const Transform3 &transformB, Vector3 &normal, float &penetrationDepth,
		Vector3 &contactPointA, Vector3 &contactPointB);

	bool ConvexConvexContact(const ConvexMesh &convexA, const Transform3 &transformA,
		const ConvexMesh &convexB, const Transform3 &transformB,
		Vector3 &normal, float &penetrationDepth,
		Vector3 &contactPointA, Vector3 &contactPointB);
	
	//検出
	void DetectCollision(const RigidbodyState *states,const Collider *colliders,unsigned int numRigidBodies,const Pair *pairs,unsigned int numPairs);
	//====================================

	//拘束ソルバー系========================
	void SolveConstraints(RigidbodyState *states, const RigidBodyElements *bodies,
		unsigned int numRigidBodies, const Pair *pairs, unsigned int numPairs,
		BallJoint *joints,
		unsigned int numJoints, unsigned int iteration,
		float bias, float slop,
		float timeStep,
		Allocator *allocator);
	//======================================

	//オブジェクト作成
	int CreateRigidBody(float* vertices, float numvertices,
		GLuint* indices, unsigned int numIndices, 
		Vector3 scale = Vector3(1.0f,1.0f,1.0f), MotionType type = MotionType::TypeActive,
		Vector3 pos = Vector3(0), float mass = 1.0f, bool sphere = false);

	//現在の物理シミュレーションのシーンを取得
	const char *PhysicsGetSceneTitle(int i);

	void SetRigidBodyPos(int i, Vector3 pos);
	void SetRigidBodyRotate(int i, Quat q);

	//オブジェクトの姿勢を変更
	void PlusRigidBodyOrientation(int i, Matrix3 rotate);

	//剛体情報の取得
	int GetNumRigidbodies();
	const RigidbodyState GetRigidBodyState(int i);
	const RigidBodyElements GetRigidBodyElements(int i);
	const Collider GetCollider(int i);

	//衝突情報の取得
};

