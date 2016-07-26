#include "Window.h";

static void Cleanup(void){
	//GLFWの終了処理
	glfwTerminate();
}

//初期化
static bool Initialize(){
	bool result = true;
	
	//GLFW初期化
	if (glfwInit() == GL_FALSE){
		//初期化失敗
		std::cout << "GLFW Init not" << std::endl;
		result = false;
	}

	//glewの初期化
	glewExperimental = GL_TRUE;
	if (glfwInit() == GL_FALSE){
		//失敗
		std::cerr << "GLFW Init not" << std::endl;
		result = false;
	
	}
	return result;
}

// 初期設定
void InitConfig()
{
}

void Draw(){

}


int main(){
	//初期化失敗
	if (!Initialize()){
		return 1;
	}

	//ウインドウを作成する
	Window window1(1200, 1200, "hello!");

	//描画処理
	while (window1.ShouldClose() == GL_FALSE){

		//バッファを入れ替える
		window1.SwapBuffers();
	}


	
	//ゲームが終わった時の処理
	atexit(Cleanup);
	return 0;
}