#include "State.h"
#include "GoalObj.h"
#include "DynamicObj.h"

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

	//�G�̐��ƃv���C���[�̐�
	mDynamicObjectNumber = 1 + stageData.enemyNumber;
	mDynamicObjects = new DynamicObj[mDynamicObjectNumber];

	//�v���C���[�̎擾�i�H�j

	//�v���C���[�̔z�u
	mDynamicObjects[0].Set(0, 0);
}

State::~State()
{
	Common::Delete(mDynamicObjects);
}

//�e�I�u�W�F�N�g�̕`��
void State::Draw()const{

}

//�e�I�u�W�F�N�g�̍X�V
void State::Update(){

}

//�N���A�������ǂ����̃`�F�b�N
bool State::hasCleared()const{
	return mGoalObj->CheckGoal();
}

//�~�X�������ǂ���
bool State::hasMissed()const{
	//��������~�X�̔��������
	return false;
}