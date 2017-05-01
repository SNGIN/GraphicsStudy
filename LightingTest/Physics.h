#pragma once
#include "PhysicsInclude.h"

class Physics
{
public:
	Physics();
	~Physics();

	//�V�~�����[�V�����n
	bool PhysicsInit();
	void PhysicsRelease();
	void PhysicsUpdate();
	//�I�u�W�F�N�g�쐬
	void CreateRigidBody(float* vertices, float numvertices, 
		unsigned short* indices, unsigned int numIndices, 
		Vector3 scale = Vector3(1.0f,1.0f,1.0f), MotionType type = MotionType::TypeActive,
		Vector3 pos = Vector3(0), float mass = 1.0f, bool sphere = false);

	//���݂̕����V�~�����[�V�����̃V�[�����擾
	const char *PhysicsGetSceneTitle(int i);

	//���̏��̎擾
	int GetNumRigidbodies();
	const RigidbodyState &GetRigidBodyState(int i);
	const RigidBodyElements &GetRigidBodyElements(int i);
	const Collider &GetCollider(int i);

	//�Փˏ��̎擾
};

