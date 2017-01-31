#include "Window.h"

//�g�嗦�̎Z�o
void Window::UpdateScale(){
	m_scale.set(m_s*m_iw, m_s*m_ih);
}

//�R���X�g���N�^
Window::Window(int width, int height, const char *title) :
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

	m_w = width;
	m_h = height;

	Resize(m_window, width, height);
}

//�f�X�g���N�^
Window::~Window(){
	glfwDestroyWindow(m_window);
}

//�J���[�o�b�t�@�����ւ��ăC�x���g����肾��
void Window::SwapBuffers(){
	//�J���[�o�b�t�@�����ւ���
	glfwSwapBuffers(m_window);

	//�C�x���g����肾��
	glfwPollEvents();
}

//�A�X�y�N�g�����肾��
GLfloat Window::GetAspect(){
	return m_aspect;
}

//�g�嗦����肾��
const vector2 Window::GetScale(){
	return m_scale;
}

void Window::Resize(GLFWwindow* const window, int width, int height){
	glViewport(0, 0, width, height);

	//this�|�C���^�𓾂�
	Window* const Instance(static_cast<Window*>(glfwGetWindowUserPointer(window)));

	Instance->m_w = width;
	Instance->m_h = height;

	if (Instance != NULL){
		Instance->mp.loadPerspective(0.5f, (float)width / (float)height, 1.0f, 20.0f);
		//�A�X�y�N�g����X�V
		Instance->m_iw = 2.0f / static_cast<GLfloat>(width);
		Instance->m_ih = 2.0f / static_cast<GLfloat>(height);

		//�g�嗦���X�V
		Instance->UpdateScale();

	}
}

int Window::Get_w(){
	return m_w;
}

int Window::Get_h(){
	return m_h;
}