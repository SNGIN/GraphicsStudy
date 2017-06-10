#pragma once
#include "PhysicsInclude.h"

class Physics
{
public:

	Physics();
	~Physics();

	//�V�~�����[�V�����n
	//bool PhysicsInit();
	void PhysicsRelease();
	void PhysicsUpdate(Vector3 Force, Vector3 Torque);

	//Integrate�n=========================
	void Integrate(RigidbodyState &states, unsigned int numRigidbodys, float timestep);
	//====================================

	//Apply�n=============================
	void ApplyExternalForce(RigidbodyState &state, const RigidBodyElements &bodyelements, const Vector3 &externalForce, const Vector3 &externalTorque, float timeStep);
	//====================================

	//Broadphase�n======================
	bool IntersectAABB(const Vector3 &centerA, const Vector3 &halfA, const Vector3 &centerB, const Vector3 &halfB);
	
	/// �u���[�h�t�F�[�Y�R�[���o�b�N<br>
	/// epxBroadPhase()�̈����Ƃ��ēn���ƁAAABB��������O�ɌĂ΂��
	/// ���ǂ�l��true�Ŕ���𑱍s , false�Ŕ�����L�����Z��
	typedef bool(*BroadPhaseCallback)(unsigned int rigidBodyIdA, unsigned int rigidBodyIdB, void *userData);

	//�u���[�h�t�F�[�Y
	void BroadPhase(RigidbodyState* states, Collider* colliders,unsigned int numRigidbodies,
		const Pair *oldPairs,const unsigned int numOldPairs,Pair *newPairs,unsigned int &numNewPairs,const unsigned int maxPairs,
		DefaultAllocator* allocator, void *userData, BroadPhaseCallback callback
		);
	//==================================

	//�Փˌ��o�n==========================
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
	
	//���o
	void DetectCollision(const RigidbodyState *states,const Collider *colliders,unsigned int numRigidBodies,const Pair *pairs,unsigned int numPairs);
	//====================================

	//�S���\���o�[�n========================
	void SolveConstraints(RigidbodyState *states, const RigidBodyElements *bodies,
		unsigned int numRigidBodies, const Pair *pairs, unsigned int numPairs,
		BallJoint *joints,
		unsigned int numJoints, unsigned int iteration,
		float bias, float slop,
		float timeStep,
		Allocator *allocator);
	//======================================

	//�I�u�W�F�N�g�쐬
	int CreateRigidBody(float* vertices, float numvertices,
		GLuint* indices, unsigned int numIndices, 
		Vector3 scale = Vector3(1.0f,1.0f,1.0f), MotionType type = MotionType::TypeActive,
		Vector3 pos = Vector3(0), float mass = 1.0f, bool sphere = false);

	//���݂̕����V�~�����[�V�����̃V�[�����擾
	const char *PhysicsGetSceneTitle(int i);

	void SetRigidBodyPos(int i, Vector3 pos);
	void SetRigidBodyRotate(int i, Quat q);

	//�I�u�W�F�N�g�̎p����ύX
	void PlusRigidBodyOrientation(int i, Matrix3 rotate);

	//���̏��̎擾
	int GetNumRigidbodies();
	const RigidbodyState GetRigidBodyState(int i);
	const RigidBodyElements GetRigidBodyElements(int i);
	const Collider GetCollider(int i);

	//�Փˏ��̎擾
};

