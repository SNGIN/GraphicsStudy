#include "Player.h"
#include "Window.h"
#include "InputManager.h"

Player::Player()
{
	//モデル読み込み(重いので最初に読み込む)
	m_bunny = new Model("bunny.obj");

	//使用するシェーダーの用意
	Shader* simple = new Shader("lambert.vert", "lambert.frag");
	Material* mat = new Material(simple);

	//モデルに対するマテリアルの設定(どのシェーダーを使うか)
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

	//シェーダの使用
	m_bunny->GetMaterial()->m_shader->Use();

	Matrix mp = Window::getMp();
	Matrix mw = Window::ReturnMV()*Translate(position.x(),position.y(),position.z());

	m_bunny->GetMaterial()->GetShader()->loadMatrix(mp, mw);
	//描画
	m_bunny->Draw();

	return d;
}
