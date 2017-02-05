#include "State.h"
#include "GoalObj.h"
#include "Player.h"
#include "InputManager.h"

//�}�b�v�̍L��
static const int WIDTH = 20;
static const int HEIGHT = 15;

//�K���ȃX�e�[�W�f�[�^(�g���\��)
struct StageData
{
	int mBlockNumber;
	int enemyNumber;
};

static StageData gStageData[] = {
	{5},
	{0},
};

State::State(int stageID) :mDynamicObjects(0), mDynamicObjectNumber(0), mstageID(stageID)
{
	//Width��height�𗘗p���Ēn�ʂ����

	//�X�e�[�W�p�����[�^�̓ǂݍ���
	const StageData& stageData = gStageData[mstageID];
	//�u���b�N������ăZ�b�g���Ă���
	
	//�S�[���I�u�W�F�N�g�����
	mGoalObj = new GoalObj();
	mGoalObj->SetFlag(StaticObj::FLAG_GOAL);

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
}

State::~State()
{
	Common::Delete(*mDynamicObjects);
	Common::Delete(mDynamicObjects);
}

//�e�I�u�W�F�N�g�̕`��
void State::Draw(){
	for (int i = 0; i < mDynamicObjectNumber; i++){
		mDynamicObjects[i]->Draw();
	}
}

//�e�I�u�W�F�N�g�̍X�V
void State::Update(){
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