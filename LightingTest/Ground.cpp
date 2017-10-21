#include "Ground.h"
#include "Window.h"
#include "InputManager.h"

//材質の色
static GLfloat ambColor[4] = { 0.6f, 0.6f, 0.6f, 1.0f };
static GLfloat diffColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
static GLfloat specColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
static GLfloat shiness = 30.0f;

Ground::Ground(GLfloat width, GLfloat height, Physics* a_physics)
{
	//TODO:回転値もメンバ変数としてrectに持たせる
	//m_Rect = new Rect(width, height);

	m_Cube = new CubeObject(Vector3(width, 0.25f, height), "PBR.vert", "PBR.frag", ambColor, diffColor, specColor, shiness);

	physics = a_physics;

	rigidBodyIndex = physics->CreateRigidBody(m_Cube->GetVertices(), m_Cube->GetNumvertices(), m_Cube->GetFaces(), m_Cube->GetNumFaces(), Vector3(width*0.1f, 0.25f, height*0.1f), MotionType::TypeStatic, Vector3(position.x(), position.y(), position.z()), 1.0, false);
	
	//Quat q = Quat::identity();
	//physics->SetRigidBodyRotate(rigidBodyIndex,q);
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
	//シェーダの使用
	m_Cube->GetMaterial()->m_shader->Use();

	Matrix mv = Window::ReturnMV()*InputManager::GetTrackBall()->Get();

	Matrix mp = Window::getMp();
	Quat q = physics->GetRigidBodyState(rigidBodyIndex).m_orientation;
	Matrix mw = mv.rotateQuat(q)*Translate(GetPos().getX(), GetPos().getY(), GetPos().getZ());

	m_Cube->GetMaterial()->GetShader()->loadMatrix(mp, mw, (Translate(GetPos().getX(), GetPos().getY(), GetPos().getZ())));
	//描画
	m_Cube->Draw();
	return s;
}