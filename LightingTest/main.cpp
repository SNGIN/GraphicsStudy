#pragma once

#include "Window.h"
#include "Shader.h"
#include "Model.h"

// 形状データ
struct Object
{
	// 頂点配列オブジェクト名
	GLuint vao;
	// データの要素数
	GLsizei count;
};

static GLfloat ambColor[4] = { 0.2f, 0.2f, 0.8f, 1.0f }; 
static GLfloat diffColor[4] = { 0.2f, 0.2f, 0.8f, 1.0f };
static GLfloat specColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat shiness = 30.0f;

const Matrix mv(Lookat(0.0f, 8.0f, 16.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f));


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
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	//ビューポート設定
	//glViewport(100, 50, 300, 300);

	//version3.2 core profileを選択
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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
	Window window1(1200, 1200, "hello!");

	//GLEWの初期化
	if (!Initialize_GLEW()){
		return 1;
	}

	//光源や色などの初期設定
	InitConfig();

	//使用するシェーダーの用意
	Shader simple("lambert.vert", "lambert.frag");
	//モデル読み込み
	Model m_bunny("bunny.obj",true);
	//モデルに対するマテリアルの設定(材質設定+どのシェーダーを使うか)
	m_bunny.MaterialSet(ambColor, diffColor, specColor, &shiness, simple);

	// ウィンドウ全体をビューポートにする
	glViewport(0, 0, window1.Get_w(), window1.Get_h());

	//カラーマスクの設定
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	//描画処理
	while (window1.ShouldClose() == GL_FALSE){
		// ウィンドウを消去する
		glClear(GL_COLOR_BUFFER_BIT);

		//配置
		m_bunny.GetMaterial()->m_shader->loadMatrix(window1.getMp(),mv*Translate(0.0f,0.0f,0.0f));

		//描画
		m_bunny.Draw();

		//バッファを入れ替える
		window1.SwapBuffers();
	}

	//ゲームが終わった時の処理
	atexit(Cleanup);
	return 0;
}