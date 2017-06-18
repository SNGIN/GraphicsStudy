#include "Ground.h"
#include "Window.h"
#include "InputManager.h"

//�ގ��̐F
static GLfloat ambColor[4] = { 0.6f, 0.6f, 0.6f, 1.0f };
static GLfloat diffColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
static GLfloat specColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
static GLfloat shiness = 30.0f;

Ground::Ground(GLfloat width, GLfloat height, Physics* a_physics)
{
	//TODO:��]�l�������o�ϐ��Ƃ���rect�Ɏ�������
	//m_Rect = new Rect(width, height);

	m_Cube = new CubeObject(Vector3(width, 0.25f, height));

	//�g�p����V�F�[�_�[�̗p��
	Shader* tile = new Shader("Tile.vert", "Tile.frag");
	Material* mat = new Material(tile, ambColor, diffColor, specColor, &shiness);

	//�}�e���A���̐ݒ�(�ǂ̃V�F�[�_�[���g����)
	//m_Rect->MaterialSet(mat);
	m_Cube->MaterialSet(mat);

	Matrix matrix;

	//�l���̓_����]�ړ��������l(m_pos�̍X�V)
	/*for (int i = 0; i < 4;  i++){
		matrix.rotateX_RVector(-1.5707963f, m_Rect->GetVertPos(i));
	}*/
	physics = a_physics;

	//rigidBodyIndex = physics->CreateRigidBody(m_Rect->GetVertPos(), 4, m_Rect->GetFace(), 6, Vector3(width, 0, height), MotionType::TypeStatic, Vector3(position.x(), position.y(), position.z()), 1.0, false);
	rigidBodyIndex = physics->CreateRigidBody(m_Cube->GetVertices(), m_Cube->GetNumvertices(), m_Cube->GetFaces(), m_Cube->GetNumFaces(), Vector3(width, 0.25f, height), MotionType::TypeStatic, Vector3(position.x(), position.y(), position.z()), 1.0, false);
	Quat q = Quat::identity();
	physics->SetRigidBodyRotate(rigidBodyIndex,q);
}


Ground::~Ground()
{
	Common::Delete(m_Cube);
}

StaticObj* Ground::Update(){
	StaticObj* s = this;
	return this;
}

StaticObj* Ground::Draw(){
	StaticObj* s = this;
	//�V�F�[�_�̎g�p
	m_Cube->GetMaterial()->m_shader->Use();

	Matrix mv = Window::ReturnMV()*InputManager::GetTrackBall()->Get();

	//Matrix3 mv = mv.loadLookat(0.0f, 1.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	Matrix mp = Window::getMp();
	Quat q = physics->GetRigidBodyState(rigidBodyIndex).m_orientation;
	Matrix mw = mv.rotateQuat(q)*Translate(position.x(), position.y(), position.z());
	//Matrix mw = mv.rotateQuat(q) *Translate(position.x(), position.y(), position.z());

	//m_Rect->GetMaterial()->GetShader()->loadMatrix(mp, mw);
	//�`��
	//m_Rect->Draw();

	m_Cube->GetMaterial()->GetShader()->loadMatrix(mp, mw);
	//�`��
	m_Cube->Draw();
	return s;
}