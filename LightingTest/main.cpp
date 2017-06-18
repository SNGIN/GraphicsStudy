#pragma once

#include "Window.h"
#include "Shader.h"
#include "Model.h"
#include "SeaquenceController.h"
#include "InputManager.h"

static void Cleanup(void){
	//GLFW�̏I������
	glfwTerminate();
}

//������
static bool Initialize_GLFW(){
	bool result = true;
	
	//GLFW������
	if (glfwInit() == GL_FALSE){
		//���������s
		std::cout << "GLFW Init not" << std::endl;
		result = false;
	}
	return result;
}

static bool Initialize_GLEW(){
	bool result = true;
	//glew�̏�����
	GLint GlewInitResult = glewInit();
	if (GLEW_OK != GlewInitResult)
	{
		printf("ERROR: %s\n", glewGetErrorString(GlewInitResult));
		result = false;
	}
	return result;
}

// �����ݒ�
void InitConfig()
{
	// �w�i�F
	glClearColor(0.2f, 0.4f, 0.6f, 0.0f);

	//version3.2 core profile��I��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

//�`��֘A�̐ݒ�
void ConfingDraw(){
	// �B�ʏ�����L���ɂ���
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	// �A���t�@�u�����f�B���O�̐ݒ�
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//�J���[�}�X�N�̐ݒ�
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
}

int main(){
	//GLFW�̏�����
	if (!Initialize_GLFW()){
		return 1;
	}

	//�E�C���h�E���쐬����
	Window::CreateWindowStart(1024, 768, "Test!");

	//GLEW�̏�����
	if (!Initialize_GLEW()){
		return 1;
	}

	//�����ݒ�=========================================
	
	InitConfig();
	//�E�B���h�E�A�V�[�P���X�R���g���[���[���쐬
	InputManager::SetMyWindow(Window::GetWindow());
	if (!SeaquenceController::instance()){
		SeaquenceController::Create();
	}
	// �E�B���h�E�S�̂��r���[�|�[�g�ɂ���
	glViewport(0, 0, Window::Get_w(), Window::Get_h());
	//�`��֘A�̐ݒ�(�����邱�Ƃ�����Α�����ݒ�ł���悤�Ɉڂ�)
	ConfingDraw();

	//=================================================

	//�`�揈��=========================================

	while (Window::ShouldClose() == GL_FALSE){
		// ��ʏ���
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//�V�[�P���X�R���g���[���[���S�Ă�Update�A�`����Ǘ�����
		SeaquenceController::instance()->Update();

		//�o�b�t�@�����ւ���
		Window::SwapBuffers();
	}

	//=================================================
	//�I��������̏���
	atexit(Cleanup);
	return 0;
}