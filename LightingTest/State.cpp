#include "State.h"
#include "GoalObj.h"
#include "Player.h"
#include "InputManager.h"
#include "Ground.h"

//�}�b�v�̍L��
static const GLfloat WIDTH = 10.0f;
static const GLfloat HEIGHT = 10.0f;

//�K���ȃX�e�[�W�f�[�^(�g���\��)
struct StageData
{
	int mBlockNumber;
	int enemyNumber;
};

static StageData gStageData[] = {
	{0},
	{0},
};


Physics* State::GetPhysics(){
	return m_Physics;
}

Ground* g;

State::State(int stageID) :mDynamicObjects(0), mDynamicObjectNumber(0), mstageID(stageID)
{

	Common::Delete(m_Physics);
	m_Physics = new Physics();

	//�X�e�[�W�p�����[�^�̓ǂݍ���
	const StageData& stageData = gStageData[mstageID];
	//�u���b�N������ăZ�b�g���Ă���

	//�I�u�W�F�N�g�̐�(�n��+�S�[��+�u���b�N��)��������p��
	mStaticObjectNumber = 1 + 1 + stageData.mBlockNumber;
	mStaticObjects = new StaticObj*[mStaticObjectNumber];

	//Width��height�𗘗p���Ēn�ʂ����
	g = new Ground(WIDTH,HEIGHT,m_Physics);
	g->Set(0, 0);
	mStaticObjects[0] = g;
	
	//�S�[���I�u�W�F�N�g�����
	GoalObj* goal = new GoalObj();
	goal->SetFlag(StaticObj::FLAG_GOAL);
	mStaticObjects[1] = goal;

	//�u���b�N��
	for (int i = 0; i < mStaticObjectNumber; i++){
		if (i>1){

			//�z�u
		}
	}

	DynamicObj* p = new Player(m_Physics);
	//�v���C���[�̔z�u

	//�G�̐��ƃv���C���[�̐�
	mDynamicObjectNumber = 1 + stageData.enemyNumber;
	mDynamicObjects = new DynamicObj*[mDynamicObjectNumber];
	
	//�v���C���[
	mDynamicObjects[0] = p;
	//�z�u
	//mDynamicObjects[0]->Set(0,1.0,0.5);

	//�G
	for (int i = 0; i < mDynamicObjectNumber; i++){
		if (i>0){

			//�z�u
		}
	}
}

State::~State()
{
	Common::Delete(*mStaticObjects);
	Common::Delete(mStaticObjects);

	Common::Delete(*mDynamicObjects);
	Common::Delete(mDynamicObjects);
}

//�e�I�u�W�F�N�g�̕`��
void State::Draw(){
	for (int i = 0; i < mStaticObjectNumber; i++){
		mStaticObjects[i]->Draw();
	}
	for (int i = 0; i < mDynamicObjectNumber; i++){
		mDynamicObjects[i]->Draw();
	}
}

//�����V�~�����[�V�����𓮂���
void State::PhysicsUpdate(){
	Vector3 force = Vector3(0);
	Vector3 torque = Vector3(0);
	if (InputManager::CheckInputMoveUp()){
		/*Matrix3 forwardRotate = Matrix3::rotationX(-0.01f);
		m_Physics->PlusRigidBodyOrientation(g->GetRigidbodyIndex(), forwardRotate);
		g->xRotate-=0.01f;*/
		force.setZ(-5.0f);
		//torque.setZ(-8.0f);
		torque.setX(-2.0f);
	}
	if (InputManager::CheckInputMoveDown()){
		/*Matrix3 forwardRotate = Matrix3::rotationX(0.01f);
		m_Physics->PlusRigidBodyOrientation(g->GetRigidbodyIndex(), forwardRotate);
		g->xRotate += 0.01f;*/
		force.setZ(5.0f);
		torque.setZ(2.0f);
	}
	if (InputManager::CheckInputMoveLeft()){
		/*Matrix3 leftrightRotate = Matrix3::rotationZ(0.01f);
		m_Physics->PlusRigidBodyOrientation(g->GetRigidbodyIndex(), leftrightRotate);
		g->zRotate -= 0.01f;*/
		force.setX(-5.0f);
		torque.setX(-2.0f);
	}
	if (InputManager::CheckInputMoveRight()){
		/*Matrix3 leftrightRotate = Matrix3::rotationZ(-0.01f);
		m_Physics->PlusRigidBodyOrientation(g->GetRigidbodyIndex(), leftrightRotate);
		g->zRotate += 0.01f;*/
		force.setX(5.0f);
		torque.setX(2.0f);
	}

	m_Physics->PhysicsUpdate(force,torque);
}

//�e�I�u�W�F�N�g�̍X�V
void State::Update(){

	for (int i = 0; i < mStaticObjectNumber; i++){
		mStaticObjects[i]->Update();
	}

	for (int i = 0; i < mDynamicObjectNumber; i++){
		mDynamicObjects[i]->Update();
	}

	if (mDynamicObjects[0]->miss){
		//TODO:�{���̓S�[���I�u�W�F�N�g�ɐG�ꂽ��
		miss = true;
	}

	//std::cout << mDynamicObjects[0]->GetPos().y() << std::endl;

	/*if (mDynamicObjects[0]->GetPos().z() < -2.5){
		std::cout << mDynamicObjects[0]->GetPos().z() << std::endl;
		//TODO:�{���̓S�[���I�u�W�F�N�g�ɐG�ꂽ��
		clear = true;
	}*/

}

//�N���A�������ǂ����̃`�F�b�N
bool State::hasCleared()const{
	return clear;
}

//�~�X�������ǂ���
bool State::hasMissed()const{
	//��������~�X�̔��������
	return miss;
}