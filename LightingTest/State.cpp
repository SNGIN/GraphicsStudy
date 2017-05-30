#include "State.h"
#include "GoalObj.h"
#include "Player.h"
#include "InputManager.h"
#include "Ground.h"

//�}�b�v�̍L��
static const GLfloat WIDTH = 6.0f;
static const GLfloat HEIGHT = 6.0f;

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
	StaticObj* g = new Ground(WIDTH,HEIGHT,m_Physics);
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
		force.setZ(-8.0f);
		torque.setZ(-8.0f);
		torque.setY(-5.0f);
	}
	if (InputManager::CheckInputMoveDown()){
		force.setZ(8.0f);
		torque.setZ(8.0f);
	}
	if (InputManager::CheckInputMoveLeft()){
		force.setX(-8.0f);
		torque.setX(-8.0f);
	}
	if (InputManager::CheckInputMoveRight()){
		force.setX(8.0f);
		torque.setX(8.0f);
	}

	m_Physics->PhysicsUpdate(force,torque);

	for (int i = 0; i < 1; i++){
	/*	std::cout << mDynamicObjects[i]->States(1).m_position.getX() << std::endl;
		std::cout << mDynamicObjects[i]->States(1).m_position.getY() << std::endl;
		std::cout << mDynamicObjects[i]->States(1).m_position.getZ() << std::endl;
		*/
	}
}

//�e�I�u�W�F�N�g�̍X�V
void State::Update(){

	for (int i = 0; i < mStaticObjectNumber; i++){
		mStaticObjects[i]->Update();
	}

	for (int i = 0; i < mDynamicObjectNumber; i++){
		mDynamicObjects[i]->Update();
	}

	if (mDynamicObjects[0]->GetPos().x() < -2.5 || mDynamicObjects[0]->GetPos().x() > 2.5){
		//TODO:�{���̓S�[���I�u�W�F�N�g�ɐG�ꂽ��
		miss = true;
	}

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