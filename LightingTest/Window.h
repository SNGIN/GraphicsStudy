#pragma once
#include "Commonheader.h"

//どのクラスからも参照される一つのオブジェクトなのでstatic
static class Window{
	//ウィンドウのハンドル
	static GLFWwindow* m_window;
	//アスペクト比
	GLfloat m_aspect;
	//横幅
	static int m_w;
	static int m_h;
	//ウインドウの高さと幅の1/2の逆数
	static GLfloat m_iw, m_ih;

	//透視投影変換行列
	static Matrix mp;

	//ワールド座標に対するデバイス座標系の拡大率
	static GLfloat m_s;

	//ワールド座標系に対する正規化デバイス座標系の拡大率
	static vector2 m_scale;

	//拡大率の算出
	void UpdateScale();

public:
	Window();

	//デストラクタ
	virtual ~Window();

	static void CreateWindow(int width, int height, const char *title);

	//ウィンドウを閉じるべきかを判定する
	static int ShouldClose(){
		return (glfwWindowShouldClose(m_window));
	}

	static Matrix ReturnMV();

	//カラーバッファを入れ替えてイベントを取りだす
	static void SwapBuffers();

	//アスペクト比を取りだす
	GLfloat GetAspect();

	//拡大率を取りだす
	const vector2 GetScale();

	//ウィンドウサイズ変更処理
	static void Resize(GLFWwindow* const window, int width, int height);

	static int Get_w();
	static int Get_h();
	static Matrix &getMp(){
		return mp;
	}
	static GLFWwindow* GetWindow(){
		return m_window;
	}
};