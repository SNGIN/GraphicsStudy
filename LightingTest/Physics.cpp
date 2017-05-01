#include "Physics.h"

// シミュレーション定義

const int maxRigidBodies = 500;
const int maxJoints = 100;
const int maxPairs = 5000;
const float timeStep = 0.016f;
const float contactBias = 0.1f;
const float contactSlop = 0.001f;
const int iteration = 10;
const Vector3 gravity(0.0f, -9.8f, 0.0f);

//計算する剛体のデータ
RigidbodyState states[maxRigidBodies];
RigidBodyElements bodies[maxRigidBodies];
Collider colliders[maxRigidBodies];
unsigned int numRigidBodies = 0;

static int rigidBodyId;

//ジョイント

//ペア

//メモリアロケータ

//パフォーマンスカウンタ

//剛体オブジェクト作成(他関数で呼ばれる)
void Physics::CreateRigidBody(float* vertices, float numvertices,
	unsigned short* indices, unsigned int numIndices,
	Vector3 scale = Vector3(1.0f, 1.0f, 1.0f), MotionType type = MotionType::TypeActive,
	Vector3 pos = Vector3(0), float mass = 1.0f,bool sphere=false){

	rigidBodyId = numRigidBodies++;

	Vector3 shapeScale(scale);

	//剛体の状態を定義
	states[rigidBodyId].Reset();
	states[rigidBodyId].m_motionType = type;
	states[rigidBodyId].m_position = pos;
	
	//剛体の情報を定義
	bodies[rigidBodyId].Reset();
	bodies[rigidBodyId].m_mass = mass;
	if (sphere){
		bodies[rigidBodyId].m_inertia = CalcInertiaBox(shapeScale,mass);
	}
	else{
		bodies[rigidBodyId].m_inertia = CalcInertiaSphere(shapeScale.xAxis,mass);
	}
	colliders[rigidBodyId].reset();

	//形状作成
	PhysicsShape shape;
	shape.reset();

	CreateConvexMesh(&shape.m_geometry, vertices, numvertices, indices, numIndices, scale);
	
	colliders[rigidBodyId].addShape(shape);
	colliders[rigidBodyId].finish();
}

Physics::Physics()
{
}


Physics::~Physics()
{
}
