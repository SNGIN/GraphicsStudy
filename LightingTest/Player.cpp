#include "Player.h"
#include "Window.h"
#include "InputManager.h"

//�ގ��̐F
static GLfloat ambColor[4] = { 0.6f, 0.6f, 0.6f, 1.0f };
static GLfloat diffColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
static GLfloat specColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
static GLfloat shiness = 30.0f;

Player::Player()
{
	//���f���ǂݍ���(�d���̂ōŏ��ɓǂݍ���)
	//m_bunny = new Model("bunny.obj");
	//TODO:face��elements�`����
	m_sphere = new SphereObject(0.25f);

	//�g�p����V�F�[�_�[�̗p��
	Shader* simple = new Shader("lambert.vert", "lambert.frag");
	Material* mat = new Material(simple,ambColor,diffColor,specColor,&shiness);

	//���f���ɑ΂���}�e���A���̐ݒ�(�ǂ̃V�F�[�_�[���g����)
	//m_bunny->MaterialSet(mat);
	m_sphere->MaterialSet(mat);

	//�����V�~�����[�V�����ɓn��
	
}


Player::~Player()
{
	Common::Delete(m_sphere);
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
	/*m_bunny->GetMaterial()->m_shader->Use();

	Matrix mv = Window::ReturnMV()*InputManager::GetTrackBall()->Get();
	Matrix mp = Window::getMp();
	Matrix mw = mv*Translate(-1,position.y(),position.z());

	m_bunny->GetMaterial()->GetShader()->loadMatrix(mp, mw);
	glCullFace(GL_BACK);
	//�`��
	m_bunny->Draw();*/

	//�V�F�[�_�̎g�p
	m_sphere->GetMaterial()->m_shader->Use();

	Matrix mv = Window::ReturnMV()*InputManager::GetTrackBall()->Get();
	Matrix mp = Window::getMp();
	Matrix mw = mv*Translate(position.x(), position.y(), position.z());

	m_sphere->GetMaterial()->GetShader()->loadMatrix(mp, mw);
	glCullFace(GL_BACK);
	//�`��
	m_sphere->Draw();

	return d;
}
