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

State::State(int stageID) :mDynamicObjects(0), mDynamicObjectNumber(0), mstageID(stageID)
{
	//�X�e�[�W�p�����[�^�̓ǂݍ���
	const StageData& stageData = gStageData[mstageID];
	//�u���b�N������ăZ�b�g���Ă���

	//�I�u�W�F�N�g�̐�(�n��+�S�[��+�u���b�N��)��������p��
	mStaticObjectNumber = 1 + 1 + stageData.mBlockNumber;
	mStaticObjects = new StaticObj*[mStaticObjectNumber];

	//Width��height�𗘗p���Ēn�ʂ����
	StaticObj* g = new Ground(WIDTH,HEIGHT);
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

	DynamicObj* p = new Player();
	//�v���C���[�̔z�u

	//�G�̐��ƃv���C���[�̐�
	mDynamicObjectNumber = 1 + stageData.enemyNumber;
	mDynamicObjects = new DynamicObj*[mDynamicObjectNumber];
	
	//�v���C���[
	mDynamicObjects[0] = p;
	//�z�u
	mDynamicObjects[0]->Set(0,2);

	//�G
	for (int i = 0; i < mDynamicObjectNumber; i++){
		if (i>0){

			//�z�u
		}
	}

	//�����V�~�����[�V�����̃f�[�^�\��


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

//�e�I�u�W�F�N�g�̍X�V
void State::Update(){

	for (int i = 0; i < mStaticObjectNumber; i++){
		mStaticObjects[i]->Update();
	}

	for (int i = 0; i < mDynamicObjectNumber; i++){
		mDynamicObjects[i]->Update();
	}

	if (mDynamicObjects[0]->Get().x() < -2.5 || mDynamicObjects[0]->Get().x() > 2.5){
		//TODO:�{���̓S�[���I�u�W�F�N�g�ɐG�ꂽ��
		miss = true;
	}

	if (mDynamicObjects[0]->Get().z() < -2.5){
		//TODO:�{���̓S�[���I�u�W�F�N�g�ɐG�ꂽ��
		clear = true;
	}

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