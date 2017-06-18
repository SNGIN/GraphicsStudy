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

	//version3.2 core profileを選択
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

//描画関連の設定
void ConfingDraw(){
	// 隠面消去を有効にする
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	// アルファブレンディングの設定
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//カラーマスクの設定
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
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

	//初期設定=========================================
	
	InitConfig();
	//ウィンドウ、シーケンスコントローラーを作成
	InputManager::SetMyWindow(Window::GetWindow());
	if (!SeaquenceController::instance()){
		SeaquenceController::Create();
	}
	// ウィンドウ全体をビューポートにする
	glViewport(0, 0, Window::Get_w(), Window::Get_h());
	//描画関連の設定(かえることがあれば他から設定できるように移す)
	ConfingDraw();

	//=================================================

	//描画処理=========================================

	while (Window::ShouldClose() == GL_FALSE){
		// 画面消去
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//シーケンスコントローラーが全てのUpdate、描画を管理する
		SeaquenceController::instance()->Update();

		//バッファを入れ替える
		Window::SwapBuffers();
	}

	//=================================================
	//終わった時の処理
	atexit(Cleanup);
	return 0;
}