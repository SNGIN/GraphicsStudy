#include "Player.h"
#include "Window.h"
#include "InputManager.h"


//�ގ��̐F
static GLfloat ambColor[4] = { 0.6f, 0.6f, 0.6f, 1.0f };
static GLfloat diffColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
static GLfloat specColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
static GLfloat shiness = 30.0f;

const int sphere_numVertices = 12;
const int sphere_numIndices = 60;
float sphere_vertices[] = {
	0.267617, -0.500000, -0.823639, -0.700629, -0.500000, -0.509037, -0.700629, -0.500000, 0.509037, 0.267617, -0.500000, 0.823639, 0.866025, -0.500000, 0.000000, 0.267617, 0.500000, -0.823639, -0.700629, 0.500000, -0.509037, -0.700629, 0.500000, 0.509037, 0.267617, 0.500000, 0.823639, 0.866025, 0.500000, 0.000000, 0.000000, -1.000000, 0.000000, 0.000000, 1.000000, 0.000000
};
GLuint sphere_indices[] = {
	0, 1, 5, 5, 1, 6, 1, 2, 6, 6, 2, 7, 2, 3, 7, 7, 3, 8, 3, 4, 8, 8, 4, 9, 4, 0, 9, 9, 0, 5, 1, 0, 10, 2, 1, 10, 3, 2, 10, 4, 3, 10, 0, 4, 10, 5, 6, 11, 6, 7, 11, 7, 8, 11, 8, 9, 11, 9, 5, 11
};

Player::Player(Physics* mPhysics)
{
	//���f���ǂݍ���(�d���̂ōŏ��ɓǂݍ���)
	//m_bunny = new Model("bunny.obj");
	//TODO:face��elements�`����
	m_sphere = new SphereObject(1.0f);

	Vector3 radius = Vector3(1.0f, 1.0f, 1.0f);

	//�g�p����V�F�[�_�[�̗p��
	Shader* simple = new Shader("lambert.vert", "lambert.frag");
	Material* mat = new Material(simple,ambColor,diffColor,specColor,&shiness);

	//���f���ɑ΂���}�e���A���̐ݒ�(�ǂ̃V�F�[�_�[���g����)
	//m_bunny->MaterialSet(mat);
	m_sphere->MaterialSet(mat);

	physics = mPhysics;

	//�����V�~�����[�V�����ɓn���č��̃f�[�^���쐬(TODO:sphereobject�ɕ����I�f�[�^����������)
	rigidBodyIndex = mPhysics->CreateRigidBody(m_sphere->GetVertices(), m_sphere->GetNumvertices(), m_sphere->GetFaces(), m_sphere->GetNumFaces(),
	//rigidBodyIndex = mPhysics->CreateRigidBody(sphere_vertices,sphere_numVertices, sphere_indices, sphere_numIndices,
	radius,MotionType::TypeActive,Vector3(0),1.0,true);
	Set(0, 3.0, 0.5);
	position.set(States(rigidBodyIndex).m_position.getX(), States(rigidBodyIndex).m_position.getY(), States(rigidBodyIndex).m_position.getZ());
	miss = false;
}


Player::~Player()
{
	Common::Delete(m_sphere);
	Common::Delete(m_gameController);
}

DynamicObj* Player::Update(){
	//�O�͂�^����
	/*if (InputManager::CheckInputMoveUp()){
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
	}*/
	position.set(States(rigidBodyIndex).m_position.getX(), States(rigidBodyIndex).m_position.getY(), States(rigidBodyIndex).m_position.getZ());
	if (States(rigidBodyIndex).m_position.getY() < -20){
		miss = true;
	}
	//std::cout << States(rigidBodyIndex).m_position.getY() << std::endl;
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
	Matrix mw = mv.modelTranslate(physics->GetRigidBodyState(rigidBodyIndex).m_orientation , Vector3(position.x(),position.y(),position.z()));

	m_sphere->GetMaterial()->GetShader()->loadMatrix(mp, mw);
	glCullFace(GL_BACK);
	//�`��
	m_sphere->Draw();

	return d;
}
