#include "Window.h"
#include "Shader.h";

// 形状データ
struct Object
{
	// 頂点配列オブジェクト名
	GLuint vao;
	// データの要素数
	GLsizei count;
};

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

// 頂点配列オブジェクトの作成
// vertices: 頂点の数
// position: 頂点の位置を格納した配列
GLuint createObject(GLuint vertices, const GLfloat(*position)[2])
{
	// 頂点配列オブジェクト
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	// 頂点バッファオブジェクト
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof (GLfloat)* 2 * vertices, position, GL_STATIC_DRAW);
	// 結合されている頂点バッファオブジェクトを in 変数から参照できるようにする
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	// 頂点配列オブジェクトの結合を解除する
	glBindVertexArray(0);
	// 頂点バッファオブジェクトの結合を解除する
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return vao;
}

// 矩形のデータを作成する
Object createRectangle()
{
	// 頂点の位置データ
	static const GLfloat position[][2] =
	{
		{ 0.5f, -0.5f },//0
		{ -0.5f, -0.5f },//1
		{ 0.5f, 0.5f },//2
		{ -0.5f, 0.5f }//3
	};
	// 頂点の数
	static const int vertices(sizeof position / sizeof position[0]);
	// 頂点配列オブジェクトの作成
	Object object;

	object.vao = createObject(vertices, position);
	object.count = vertices;
	return object;
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

	// プログラムオブジェクトの作成
	const GLuint program(loadProgram("point.vert", "pv", "point.frag", "fc"));

	InitConfig();

	const Object object(createRectangle());

	//描画処理
	while (window1.ShouldClose() == GL_FALSE){
		// ウィンドウを消去する
		glClear(GL_COLOR_BUFFER_BIT);
		//シェーダプログラムの適用
		glUseProgram(program);

		glBindVertexArray(object.vao);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, object.count);

		//バッファを入れ替える
		window1.SwapBuffers();
	}

	//ゲームが終わった時の処理
	atexit(Cleanup);
	return 0;
}