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
	//���g�̎��̂����
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
	//�V�[�P���X�N���X��Boot�����N���X�Ɏ���
	//�V�[�P���X�N���X��update�֐��͎��g�̃|�C���^��������
	//�h���N���X��Update�����s����(�ǂ�Update�����s���邩�̓|�C���^�ϊ��ɂ�鎩������)
	Boot* nextSeaquence = mSeaquence->Update(this);
	if (nextSeaquence != mSeaquence){
		Seaquence* casted = dynamic_cast<Seaquence*>(nextSeaquence);
		
		//���݂̃V�[�P���X���̂ĂĎ���
		Common::Delete(mSeaquence);
		mSeaquence = casted;
	}
	//���񔻒肷��̂�0�ɖ߂��Ă���
	nextSeaquence = 0;
}

