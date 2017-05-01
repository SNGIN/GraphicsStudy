#include "Player.h"
#include "Window.h"
#include "InputManager.h"

//材質の色
static GLfloat ambColor[4] = { 0.6f, 0.6f, 0.6f, 1.0f };
static GLfloat diffColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
static GLfloat specColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
static GLfloat shiness = 30.0f;

Player::Player()
{
	//モデル読み込み(重いので最初に読み込む)
	//m_bunny = new Model("bunny.obj");
	//TODO:faceをelements形式で
	m_sphere = new SphereObject(0.25f);

	//使用するシェーダーの用意
	Shader* simple = new Shader("lambert.vert", "lambert.frag");
	Material* mat = new Material(simple,ambColor,diffColor,specColor,&shiness);

	//モデルに対するマテリアルの設定(どのシェーダーを使うか)
	//m_bunny->MaterialSet(mat);
	m_sphere->MaterialSet(mat);

	//物理シミュレーションに渡す
	
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

	//シェーダの使用
	/*m_bunny->GetMaterial()->m_shader->Use();

	Matrix mv = Window::ReturnMV()*InputManager::GetTrackBall()->Get();
	Matrix mp = Window::getMp();
	Matrix mw = mv*Translate(-1,position.y(),position.z());

	m_bunny->GetMaterial()->GetShader()->loadMatrix(mp, mw);
	glCullFace(GL_BACK);
	//描画
	m_bunny->Draw();*/

	//シェーダの使用
	m_sphere->GetMaterial()->m_shader->Use();

	Matrix mv = Window::ReturnMV()*InputManager::GetTrackBall()->Get();
	Matrix mp = Window::getMp();
	Matrix mw = mv*Translate(position.x(), position.y(), position.z());

	m_sphere->GetMaterial()->GetShader()->loadMatrix(mp, mw);
	glCullFace(GL_BACK);
	//描画
	m_sphere->Draw();

	return d;
}
