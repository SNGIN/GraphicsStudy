#pragma once

#include "Window.h"
#include "Shader.h"
#include "Model.h"
#include "SeaquenceController.h"
#include "InputManager.h"

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

// 球のデータの分割数
#define SLICES 64
#define STACKS 32

// 球のデータの頂点数と面数
#define VERTICES ((SLICES + 1) * (STACKS + 1))
#define FACES (SLICES * STACKS * 2)

//
// 球のデータの作成
//
static void makeSphere(float radius, int slices, int stacks,
	GLfloat(*pv)[3], GLfloat(*nv)[3], GLfloat(*tv)[2], GLuint(*f)[3])
{
	// 頂点の位置とテクスチャ座標を求める
	for (int k = 0, j = 0; j <= stacks; ++j)
	{
		float t = (float)j / (float)stacks;
		float ph = 3.141593f * t;
		float y = cosf(ph);
		float r = sinf(ph);

		for (int i = 0; i <= slices; ++i)
		{
			float s = (float)i / (float)slices;
			float th = -2.0f * 3.141593f * s;
			float x = r * cosf(th);
			float z = r * sinf(th);

			// 頂点の座標値
			pv[k][0] = x * radius;
			pv[k][1] = y * radius;
			pv[k][2] = z * radius;

			// 頂点の法線ベクトル
			nv[k][0] = x;
			nv[k][1] = y;
			nv[k][2] = z;

			// 頂点のテクスチャ座標値
			tv[k][0] = s;
			tv[k][1] = t;

			++k;
		}
	}

	// 面の指標を求める
	for (int k = 0, j = 0; j < stacks; ++j)
	{
		for (int i = 0; i < slices; ++i)
		{
			int count = (slices + 1) * j + i;

			// 上半分の三角形
			f[k][0] = count;
			f[k][1] = count + slices + 2;
			f[k][2] = count + 1;
			++k;

			// 下半分の三角形
			f[k][0] = count;
			f[k][1] = count + slices + 1;
			f[k][2] = count + slices + 2;
			++k;
		}
	}
}

int main(){
	//GLFWの初期化
	if (!Initialize_GLFW()){
		return 1;
	}

	//ウインドウを作成する
	Window::CreateWindowStart(1024, 768, "Test!");

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

		// シェーダプログラムの使用終了
		glUseProgram(0);
		//バッファを入れ替える
		Window::SwapBuffers();

	}

	//終わった時の処理
	atexit(Cleanup);
	return 0;
}