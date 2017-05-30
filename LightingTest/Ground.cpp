#include "Ground.h"
#include "Window.h"
#include "InputManager.h"

//材質の色
static GLfloat ambColor[4] = { 0.6f, 0.6f, 0.6f, 1.0f };
static GLfloat diffColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
static GLfloat specColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
static GLfloat shiness = 30.0f;

Ground::Ground(GLfloat width,GLfloat height,Physics* a_physics)
{
	//TODO:回転値もメンバ変数としてrectに持たせる
	m_Rect = new Rect(width, height);

	//使用するシェーダーの用意
	Shader* tile = new Shader("Tile.vert", "Tile.frag");
	Material* mat = new Material(tile,ambColor,diffColor,specColor,&shiness);

	//マテリアルの設定(どのシェーダーを使うか)
	m_Rect->MaterialSet(mat);

	Matrix matrix;

	//四隅の点を回転移動させた値(m_posの更新)
	for (int i = 0; i < 4; i++){
		matrix.rotateX_RVector(-1.5707963f, m_Rect->GetVertPos(i));
	}
	physics = a_physics;

	rigidBodyIndex = physics->CreateRigidBody(m_Rect->GetVertPos(), 4, m_Rect->GetFace(), 6, Vector3(width, 0, height), MotionType::TypeStatic, Vector3(position.x(), position.y(), position.z()), 1.0, false);
}


Ground::~Ground()
{
	Common::Delete(m_Rect);
}

StaticObj* Ground::Update(){
	StaticObj* s = this;
	return this;
}

StaticObj* Ground::Draw(){
	StaticObj* s = this;
	//シェーダの使用
	m_Rect->GetMaterial()->m_shader->Use();

	Matrix mv = Window::ReturnMV()*InputManager::GetTrackBall()->Get();

	//Matrix mv = mv.loadLookat(0.0f, 1.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	Matrix mp = Window::getMp();
	Matrix mw = mv.rotateX(-1.5707963f)*Translate(position.x(), position.y(), position.z());

	m_Rect->GetMaterial()->GetShader()->loadMatrix(mp, mw);
	//描画
	m_Rect->mtriangle->Draw();
	return s;
}

