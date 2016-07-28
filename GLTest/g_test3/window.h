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
	//�E�B���h�E�̃n���h��
	GLFWwindow* const m_window;
	//�A�X�y�N�g��
	GLfloat m_aspect;
	//�E�C���h�E�̍����ƕ���1/2�̋t��
	GLfloat m_iw, m_ih;

	//���[���h���W�ɑ΂���f�o�C�X���W�n�̊g�嗦
	GLfloat m_s;

	//���[���h���W�n�ɑ΂��鐳�K���f�o�C�X���W�n�̊g�嗦
	vector2 m_scale;

	//�g�嗦�̎Z�o
	void UpdateScale();
public:
	Window(int width, int height, const char *title);

	//�f�X�g���N�^
	virtual ~Window();

	//�E�B���h�E�����ׂ����𔻒肷��
	int ShouldClose(){
		return (glfwWindowShouldClose(m_window));
	}


	//�J���[�o�b�t�@�����ւ��ăC�x���g����肾��
	void SwapBuffers();

	//�A�X�y�N�g�����肾��
	GLfloat GetAspect();

	//�g�嗦����肾��
	const vector2 GetScale();

	//�E�B���h�E�T�C�Y�ύX����
	static void Resize(GLFWwindow* const window, int width, int height);
};