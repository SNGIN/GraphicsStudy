#pragma once

#include "Window.h"
#include "Shader.h"
#include "Model.h"
#include "SeaquenceController.h"
#include "InputManager.h"


//材質の色
static GLfloat ambColor[4] = { 0.6f, 0.6f, 0.6f, 1.0f }; 
static GLfloat diffColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
static GLfloat specColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
static GLfloat shiness = 30.0f;

//光源特性
/*struct Light
{
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat position[4];

	// シェーダーソースでの場所
	GLint pl;         // 光源位置の uniform 変数の場所
	GLint lamb;       // 光源強度の環境光成分の uniform 変数の場所
	GLint ldiff;      // 光源強度の拡散反射光成分の uniform 変数の場所
	GLint lspec;      // 光源強度の鏡面反射光成分の uniform 変数の場所
};*/

static void Cleanup(void){
	//GLFWの終了処理
	glfwTerminate();
}

//初期化
static bool Initialize_GLFW(){
	bool result = true;
	
	//GLFW初期化
	if (glfwInit() == GL_FALSE){
		//初期化失敗
		std::cout << "GLFW Init not" << std::endl;
		result = false;
	}
	return result;
}

static bool Initialize_GLEW(){
	bool result = true;
	//glewの初期化
	GLint GlewInitResult = glewInit();
	if (GLEW_OK != GlewInitResult)
	{
		printf("ERROR: %s\n", glewGetErrorString(GlewInitResult));
		result = false;
	}
	return result;
}

// 初期設定
void InitConfig()
{
	// 背景色
	glClearColor(0.2f, 0.4f, 0.6f, 0.0f);

	// 隠面消去を有効にする
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// アルファブレンディングの設定
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//ビューポート設定
	//glViewport(100, 50, 300, 300);

	//version3.2 core profileを選択
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Draw(){

}

int main(){
	//GLFWの初期化
	if (!Initialize_GLFW()){
		return 1;
	}

	//ウインドウを作成する
	Window::CreateWindow(1024, 768, "Test!");

	//GLEWの初期化
	if (!Initialize_GLEW()){
		return 1;
	}

	//初期設定
	InitConfig();
	InputManager::SetMyWindow(Window::GetWindow());
	if (!SeaquenceController::instance()){
		SeaquenceController::Create();
	}

	//TODO:グラフィック系にうつす
	//使用するシェーダーの用意
	Shader simple("lambert.vert", "lambert.frag");

	//モデル読み込み
	//Model* m_bunny = new Model("bunny.obj");
	//モデルに対するマテリアルの設定(材質設定+どのシェーダーを使うか)
	//m_bunny->MaterialSet(simple);

	// ウィンドウ全体をビューポートにする
	glViewport(0, 0, Window::Get_w(), Window::Get_h());

	//カラーマスクの設定
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	//描画処理
	while (Window::ShouldClose() == GL_FALSE){
		// 画面消去
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//シーケンス処理のチェック
		SeaquenceController::instance()->Update();

		//シェーダの使用
		//m_bunny->GetMaterial()->m_shader->Use();
		//m_bunny->GetMaterial()->m_shader->loadMatrix(Window::getMp(), Window::ReturnMV()*Translate(0.0f, 0.0f, -2.0f));

		//描画
		//m_bunny->Draw();
		// シェーダプログラムの使用終了
		glUseProgram(0);
		//バッファを入れ替える
		Window::SwapBuffers();

	}

	//終わった時の処理
	atexit(Cleanup);
	return 0;
}