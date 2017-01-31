#pragma once
#include "Commonheader.h"

class Window{
	//ウィンドウのハンドル
	GLFWwindow* const m_window;
	//アスペクト比
	GLfloat m_aspect;
	//ウインドウの高さと幅の1/2の逆数
	GLfloat m_iw, m_ih;

	//ワールド座標に対するデバイス座標系の拡大率
	GLfloat m_s;

	//ワールド座標系に対する正規化デバイス座標系の拡大率
	vector2 m_scale;

	//拡大率の算出
	void UpdateScale();
public:
	Window(int width, int height, const char *title);

	//デストラクタ
	virtual ~Window();

	//ウィンドウを閉じるべきかを判定する
	int ShouldClose(){
		return (glfwWindowShouldClose(m_window));
	}


	//カラーバッファを入れ替えてイベントを取りだす
	void SwapBuffers();

	//アスペクト比を取りだす
	GLfloat GetAspect();

	//拡大率を取りだす
	const vector2 GetScale();

	//ウィンドウサイズ変更処理
	static void Resize(GLFWwindow* const window, int width, int height);
};