#include "State.h"
#include "GoalObj.h"
#include "Player.h"
#include "InputManager.h"
#include "Ground.h"
#include "Block.h"

//�}�b�v�̍L��
static const GLfloat WIDTH = 10.0f;
static const GLfloat HEIGHT = 10.0f;

//�K���ȃX�e�[�W�f�[�^(�g���\��)
struct StagePositionData
{
	Vector3 Pos;
};

StagePositionData blockData1[] = {
	{ Vector3(-5.0f, 1.25f, 0.0f) },
	{ Vector3(1.0f, 1.25f, 3.0f) },
	{ Vector3(4.0f, 1.25f, -4.0f) },
	{ Vector3(-3.0f, 1.25f, -2.0f) },
	{ Vector3(5.0f, 1.25f, 0.0f) },
};

StagePositionData itemData1[] = {
	{ Vector3(-1.0f, 0.0f, 3.0f) },
	{ Vector3(2.0f, 0.0f, 1.0f) },
	{ Vector3(0.0f, 0.0f, 2.0f) },
	{ Vector3(-3.0f, 0.0f, 1.0f) },
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
	int blockNum = 5;
	int itemNum = 0;

	//�I�u�W�F�N�g�̐�(�n��+�S�[��+�u���b�N��)��������p��
	mStaticObjectNumber = 1 + blockNum;
	mStaticObjects = new StaticObj*[mStaticObjectNumber];

	//Width��height�𗘗p���Ēn�ʂ����
	g = new Ground(WIDTH,HEIGHT,m_Physics);
	g->Set(0, 0);
	mStaticObjects[0] = g;
	
	for (int i = 0; i < blockNum; i++){
		//�u���b�N������ăZ�b�g���Ă���
		const StagePositionData stageBlockData = blockData1[i];
		mStaticObjects[1+i] = new Block(1.0f, 1.0f, 1.0f, stageBlockData.Pos, m_Physics);
	}

	//�A�C�e���I�u�W�F�N�g�����
	GoalObj* goal = new GoalObj();
	goal->SetFlag(StaticObj::FLAG_GOAL);
	//mStaticObjects[1] = goal;

	DynamicObj* p = new Player(m_Physics);
	//�v���C���[�̔z�u

	//�G�̐��ƃv���C���[�̐�
	mDynamicObjectNumber = 1 + itemNum;
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
		force.setZ(-7.0f);
		//torque.setZ(-8.0f);
		torque.setX(-4.0f);
	}
	if (InputManager::CheckInputMoveDown()){
		/*Matrix3 forwardRotate = Matrix3::rotationX(0.01f);
		m_Physics->PlusRigidBodyOrientation(g->GetRigidbodyIndex(), forwardRotate);
		g->xRotate += 0.01f;*/
		force.setZ(7.0f);
		torque.setZ(4.0f);
	}
	if (InputManager::CheckInputMoveLeft()){
		/*Matrix3 leftrightRotate = Matrix3::rotationZ(0.01f);
		m_Physics->PlusRigidBodyOrientation(g->GetRigidbodyIndex(), leftrightRotate);
		g->zRotate -= 0.01f;*/
		force.setX(-7.0f);
		torque.setX(-4.0f);
	}
	if (InputManager::CheckInputMoveRight()){
		/*Matrix3 leftrightRotate = Matrix3::rotationZ(-0.01f);
		m_Physics->PlusRigidBodyOrientation(g->GetRigidbodyIndex(), leftrightRotate);
		g->zRotate += 0.01f;*/
		force.setX(7.0f);
		torque.setX(4.0f);
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