#pragma once
#include "Commonheader.h"

class Window{
	//�E�B���h�E�̃n���h��
	GLFWwindow* const m_window;
	//�A�X�y�N�g��
	GLfloat m_aspect;
	//����
	int m_w;
	int m_h;
	//�E�C���h�E�̍����ƕ���1/2�̋t��
	GLfloat m_iw, m_ih;

	//�������e�ϊ��s��
	Matrix mp;

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

	int Get_w();
	int Get_h();
	const Matrix &getMp()const{
		return mp;
	}
};