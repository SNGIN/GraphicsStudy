#include "SeaquenceController.h"
#include "Title.h"

SeaquenceController* SeaquenceController::mInstance = 0;

SeaquenceController::SeaquenceController() :mSeaquence(0)
{
	//�ŏ��Ƀ^�C�g�������
	mSeaquence = new Title();
}


SeaquenceController::~SeaquenceController()
{
	//�V�[�P���X�̃|�C���^�I������
	Common::Delete(mSeaquence);
}

void SeaquenceController::Create(){
	//���̂����
	mInstance = new SeaquenceController();
}

void SeaquenceController::Destroy(){
	//���g�̃|�C���^�I������
	Common::Delete(mInstance);
}

SeaquenceController* SeaquenceController::instance(){
	return mInstance;
}

void SeaquenceController::Update(){
	//�h���N���X��Update�����s����
	Boot* nextSeaquence = mSeaquence->Update(this);
	if (nextSeaquence != mSeaquence){
		//�J�ڔ���
		Seaquence* casted = dynamic_cast<Seaquence*>(nextSeaquence);
		//���݂̃V�[�P���X���̂ĂĎ���
		Common::Delete(mSeaquence);
		mSeaquence = casted;
	}
	nextSeaquence = 0;
}

