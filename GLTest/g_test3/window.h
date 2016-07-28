#include "Commonheader.h"
#include<vector>


class vector2{
	GLfloat m_x, m_y;
public:
	~vector2(){}
	vector2(){}
	vector2(GLfloat x, GLfloat y){m_x = x; y = m_y;}
	GLfloat x() const { return m_x; }
	GLfloat y() const { return m_y; }

	void set(GLfloat a, GLfloat b){ m_x = a; m_y = b; }
	void setx(GLfloat a){ m_x = a; }
	void sety(GLfloat a){ m_y = a; }
	vector2& operator +=(const vector2 &a) { m_x += a.x(); m_y += a.y(); return *this; }
	vector2& operator -=(const vector2 &a) { m_x -= a.x(); m_y -= a.y(); return *this; }
	vector2& operator /=(const GLfloat &a) { m_x /= a; m_y /= a; return *this; }
	vector2 operator +() const { return *this; }
	vector2 operator -() const { vector2 a(0.0, 0.0); a -= *this; return *this; }
};

static inline vector2 operator +(const vector2 &a, const vector2 &b) { vector2 c = a; c += b; return c; }
static inline vector2 operator -(const vector2 &a, const vector2 &b) { vector2 c = a; c -= b; return c; }
static inline vector2 operator /(const vector2 &a, const vector2 &b) { vector2 c = a; c /= b; return c; }
static inline bool operator ==(const vector2 &a, const vector2 &b){
	if (a.x() == b.x() && a.y() == b.y()){
		return true;
	}
	else{
		return false;
	}
}

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