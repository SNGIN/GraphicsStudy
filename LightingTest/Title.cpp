#include "Title.h"
#include "InputManager.h"
#include "SeaquenceController.h"
#include "GameSeaquenceController.h"
#include "SimpleImageMaterial.h"

Title::Title()
{
	//�E�B���h�E�T�C�Y��Rect�I�u�W�F�N�g�p��
	mrect = new Rect(1, 1);
	//�V�F�[�_�[�g�p��`
	Shader* titleShader = new Shader("simpleTex.vert","simpleTex.frag");

	//�e�N�X�`����`
	Texture* tex = new Texture("texture1.tga", GL_RGBA);

	//�}�e���A����`
	SimpleImageMaterial* mat = new SimpleImageMaterial(titleShader,tex);
	mrect->SetMaterial(mat);
}


Title::~Title()
{
	//�^�C�g���Ŏg���Ă郊�\�[�X�̉��
	Common::Delete(mrect);
}

Boot* Title::Update(SeaquenceController* controller){
	Boot* next = this;

	std::cout << "Title" << std::endl;
	mrect->Draw();
	if (InputManager::CheckInputSpace()){
		next = new GameSeaquenceController();
	}
	return next;
}