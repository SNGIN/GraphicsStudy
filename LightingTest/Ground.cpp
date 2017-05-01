#include "Ground.h"
#include "Window.h"
#include "InputManager.h"

//材質の色
static GLfloat ambColor[4] = { 0.6f, 0.6f, 0.6f, 1.0f };
static GLfloat diffColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
static GLfloat specColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
static GLfloat shiness = 30.0f;

Ground::Ground(GLfloat width,GLfloat height)
{
	m_Rect = new Rect(width, height);

	//使用するシェーダーの用意
	Shader* tile = new Shader("Tile.vert", "Tile.frag");
	Material* mat = new Material(tile,ambColor,diffColor,specColor,&shiness);

	//マテリアルの設定(どのシェーダーを使うか)
	m_Rect->MaterialSet(mat);
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

