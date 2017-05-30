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
BallJoint joints[maxJoints];
unsigned int numJoints = 0;

//ペア
unsigned int pairSwap;
unsigned int numPairs[2];
Pair pairs[2][maxPairs];

static int frame = 0;

//メモリアロケータ
DefaultAllocator allocator;

//パフォーマンスカウンタ

//剛体オブジェクト作成(他関数で呼ばれる)
//Indexでアクセスする
int Physics::CreateRigidBody(float* vertices, float numvertices,
	GLuint* indices, unsigned int numIndices,
	Vector3 scale, MotionType type,Vector3 pos, float mass,bool sphere){

	rigidBodyId = numRigidBodies++;

	Vector3 shapeScale(scale);

	//剛体の状態を定義
	states[rigidBodyId].Reset();
	states[rigidBodyId].m_motionType = type;
	states[rigidBodyId].m_position = pos;
	
	//剛体の情報を定義
	bodies[rigidBodyId].Reset();
	bodies[rigidBodyId].m_mass = mass;
	if (type == MotionType::TypeActive){
		if (sphere){
			bodies[rigidBodyId].m_inertia = CalcInertiaBox(shapeScale, mass);
		}
		else{
			bodies[rigidBodyId].m_inertia = CalcInertiaSphere(shapeScale.getX(), mass);
		}
	}
	colliders[rigidBodyId].reset();

	//形状作成
	PhysicsShape shape;
	shape.reset();

	CreateConvexMesh(&shape.m_geometry, 
		vertices, 
		numvertices, 
		indices, 
		numIndices, 
		scale);
	
	colliders[rigidBodyId].addShape(shape);
	colliders[rigidBodyId].finish();

	return rigidBodyId;
}

Physics::Physics()
{
}


Physics::~Physics()
{
}


//シミュレーション系
void Physics::PhysicsUpdate(Vector3 Force,Vector3 Torque){
	//外力
	for (unsigned int i = 0; i < numRigidBodies; i++){
		Vector3 externalForce = gravity * bodies[i].m_mass + Force;
		Vector3 externalTorque(Torque);
		ApplyExternalForce(states[i], bodies[i], externalForce, externalTorque, timeStep);
	}
	//ブロードフェーズ
	BroadPhase(states, colliders, numRigidBodies, pairs[1 - pairSwap],
		numPairs[1 - pairSwap], pairs[pairSwap], numPairs[pairSwap], maxPairs, &allocator, NULL, NULL);

	//コリジョン
	DetectCollision(states, colliders, numRigidBodies, pairs[pairSwap], numPairs[pairSwap]);

	//拘束ソルバー
	SolveConstraints(states, bodies, numRigidBodies,
		pairs[pairSwap], numPairs[pairSwap],
		joints, numJoints,iteration, contactBias, contactSlop, timeStep, &allocator);

	//積分
	for (unsigned int i = 0; i < numRigidBodies; i++){
		Integrate(states[i], numRigidBodies, timeStep);
	}
}
void Physics::PhysicsRelease(){

}

void Physics::SetRigidBodyPos(int i, Vector3 pos){
	states[i].m_position = pos;
}

const Collider Physics::GetCollider(int i){
	return colliders[i];
}

const RigidBodyElements Physics::GetRigidBodyElements(int i){
	return bodies[i];
}

const RigidbodyState Physics::GetRigidBodyState(int i){
	return states[i];
}