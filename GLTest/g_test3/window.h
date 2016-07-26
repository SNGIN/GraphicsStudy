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
static inline vector2 operator /(const vector2 &a, const double &b) { vector2 c = a; c /= b; return c; }
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
	void UpdateScale(){
		m_scale.set(m_s*m_iw,m_s*m_ih);
	}
public:

	//�R���X�g���N�^
	Window(int width, int height, const char *title) :
		m_window(glfwCreateWindow(width, height, title, NULL, NULL))
		, m_iw(2.0f / static_cast<GLfloat>(width))
		, m_ih(2.0f / static_cast<GLfloat>(height))
		, m_s(100.0f)
	{
		if (m_window == NULL){
			//�E�B���h�E���쐬�ł��Ȃ�����
			std::cerr << "Can't" << std::endl;
			exit(1);
		}

		//���݂̃E�B���h�E�������Ώۂ�
		glfwMakeContextCurrent(m_window);

		//�쐬�����E�B���h�E�ɑ΂���ݒ�
		glfwSwapInterval(1);

		glfwSetFramebufferSizeCallback(m_window, Resize);

		//���̃C���X�^���X��his�|�C���^���L�^
		glfwSetWindowUserPointer(m_window, this);

		//���[���h���W�n�ɑ΂��鐳�K���f�o�C�X���W�n�̊g�嗦�̏����l
		//updateScale();
		Resize(m_window, width, height);
	}

	//�f�X�g���N�^
	virtual ~Window(){
		glfwDestroyWindow(m_window);
	}

	//�E�B���h�E�����ׂ����𔻒肷��
	int ShouldClose(){
		return (glfwWindowShouldClose(m_window));
	}


	//�J���[�o�b�t�@�����ւ��ăC�x���g����肾��
	void SwapBuffers(){
		//�J���[�o�b�t�@�����ւ���
		glfwSwapBuffers(m_window);

		//�C�x���g����肾��
		glfwPollEvents();
	}

	//�A�X�y�N�g�����肾��
	GLfloat GetAspect(){
		return m_aspect;
	}

	//�g�嗦����肾��
	const vector2 GetScale(){
		return m_scale;
	}

	//�E�B���h�E�T�C�Y�ύX����
	static void Resize(GLFWwindow* const window, int width, int height){
		glViewport(0, 0, width, height);

		//this�|�C���^�𓾂�
		Window* const Instance(static_cast<Window*>(glfwGetWindowUserPointer(window)));

		if (Instance != NULL){
			//�A�X�y�N�g����X�V
			Instance->m_iw = 2.0f / static_cast<GLfloat>(width);
			Instance->m_ih = 2.0f / static_cast<GLfloat>(height);

			//�g�嗦���X�V
			Instance->UpdateScale();

		}
	}
};