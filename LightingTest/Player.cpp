#include "Player.h"
#include "Window.h"
#include "InputManager.h"

Player::Player()
{
	//���f���ǂݍ���(�d���̂ōŏ��ɓǂݍ���)
	m_bunny = new Model("bunny.obj");

	//�g�p����V�F�[�_�[�̗p��
	Shader* simple = new Shader("lambert.vert", "lambert.frag");
	Material* mat = new Material(simple);

	//���f���ɑ΂���}�e���A���̐ݒ�(�ǂ̃V�F�[�_�[���g����)
	m_bunny->MaterialSet(mat);
}


Player::~Player()
{
}

DynamicObj* Player::Update(){
	if (InputManager::CheckInputMoveUp()){
		position.setz(position.z()- speed);
	}
	if (InputManager::CheckInputMoveDown()){
		position.setz(position.z() + speed);
	}
	if (InputManager::CheckInputMoveLeft()){
		position.setx(position.x() - speed);
	}
	if (InputManager::CheckInputMoveRight()){
		position.setx(position.x() + speed);
	}
	return this;
}

DynamicObj* Player::Draw(){

	DynamicObj* d = this;

	//�V�F�[�_�̎g�p
	m_bunny->GetMaterial()->m_shader->Use();

	Matrix mp = Window::getMp();
	Matrix mw = Window::ReturnMV()*Translate(position.x(),position.y(),position.z());

	m_bunny->GetMaterial()->GetShader()->loadMatrix(mp, mw);
	//�`��
	m_bunny->Draw();

	return d;
}
