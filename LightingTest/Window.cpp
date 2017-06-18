#include "Window.h"

//static変数群
GLFWwindow* Window::m_window = 0;
//横幅
int Window::m_w = 0;
int Window::m_h = 0;
//ウインドウの高さと幅の1/2の逆数
GLfloat Window::m_iw = 0;
GLfloat Window::m_ih = 0;

//透視投影変換行列
Matrix Window::mp=Matrix();

//ワールド座標に対するデバイス座標系の拡大率
GLfloat Window::m_s = 0;

//ワールド座標系に対する正規化デバイス座標系の拡大率
vector2 Window::m_scale = vector2(0,0);

//拡大率の算出
void Window::UpdateScale(){
	m_scale.set(m_s*m_iw, m_s*m_ih);
}

//コンストラクタ
Window::Window(){
}

void Window::CreateWindowStart(int width, int height, const char *title){

	m_window = glfwCreateWindow(width, height, title, NULL, NULL);
	m_iw = (2.0f / static_cast<GLfloat>(width));
	m_ih = (2.0f / static_cast<GLfloat>(height));
	m_s = (100.0f);

		if (m_window == NULL){
			//ウィンドウが作成できなかった
			std::cerr << "Can't" << std::endl;
			exit(1);
		}

		//現在のウィンドウを処理対象に
		glfwMakeContextCurrent(m_window);

		//作成したウィンドウに対する設定
		glfwSwapInterval(1);

		glfwSetFramebufferSizeCallback(m_window, Resize);

		//このインスタンスのthisポインタを記録
		glfwSetWindowUserPointer(m_window,m_window);

		//ワールド座標系に対する正規化デバイス座標系の拡大率の初期値
		//updateScale();

		m_w = width;
		m_h = height;

		Resize(m_window, width, height);

}

//デストラクタ
Window::~Window(){
	glfwDestroyWindow(m_window);
}

//カラーバッファを入れ替えてイベントを取りだす
void Window::SwapBuffers(){
	//カラーバッファを入れ替える
	glfwSwapBuffers(m_window);

	//イベントを取りだす
	glfwPollEvents();
}

//アスペクト比を取りだす
GLfloat Window::GetAspect(){
	return m_aspect;
}

//拡大率を取りだす
const vector2 Window::GetScale(){
	return m_scale;
}

void Window::Resize(GLFWwindow* const window, int width, int height){
	glViewport(0, 0, width, height);

	//thisポインタを得る
	Window* const Instance(static_cast<Window*>(glfwGetWindowUserPointer(window)));

	Instance->m_w = width;
	Instance->m_h = height;

	if (Instance != NULL){
		Instance->mp.loadPerspective(0.5f, (float)width / (float)height, 1.0f, 200.0f);
		//アスペクト比を更新
		Instance->m_iw = 2.0f / static_cast<GLfloat>(width);
		Instance->m_ih = 2.0f / static_cast<GLfloat>(height);

		//拡大率を更新
		Instance->UpdateScale();

	}
}

int Window::Get_w(){
	return m_w;
}

int Window::Get_h(){
	return m_h;
}

Matrix Window::ReturnMV(){
	//ビューの変換行列(注視点の設定)
	return Matrix(Lookat(0.0f, 35.0f, 30.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f));
}