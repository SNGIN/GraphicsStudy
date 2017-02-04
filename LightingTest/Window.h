#pragma once
#include "Commonheader.h"

//�ǂ̃N���X������Q�Ƃ�����̃I�u�W�F�N�g�Ȃ̂�static
static class Window{
	//�E�B���h�E�̃n���h��
	static GLFWwindow* m_window;
	//�A�X�y�N�g��
	GLfloat m_aspect;
	//����
	static int m_w;
	static int m_h;
	//�E�C���h�E�̍����ƕ���1/2�̋t��
	static GLfloat m_iw, m_ih;

	//�������e�ϊ��s��
	static Matrix mp;

	//���[���h���W�ɑ΂���f�o�C�X���W�n�̊g�嗦
	static GLfloat m_s;

	//���[���h���W�n�ɑ΂��鐳�K���f�o�C�X���W�n�̊g�嗦
	static vector2 m_scale;

	//�g�嗦�̎Z�o
	void UpdateScale();

public:
	Window();

	//�f�X�g���N�^
	virtual ~Window();

	static void CreateWindow(int width, int height, const char *title);

	//�E�B���h�E�����ׂ����𔻒肷��
	static int ShouldClose(){
		return (glfwWindowShouldClose(m_window));
	}

	static Matrix ReturnMV();

	//�J���[�o�b�t�@�����ւ��ăC�x���g����肾��
	static void SwapBuffers();

	//�A�X�y�N�g�����肾��
	GLfloat GetAspect();

	//�g�嗦����肾��
	const vector2 GetScale();

	//�E�B���h�E�T�C�Y�ύX����
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