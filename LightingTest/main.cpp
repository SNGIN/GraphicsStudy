#pragma once

#include "Window.h"
#include "Shader.h"
#include "Model.h"
#include "SeaquenceController.h"
#include "InputManager.h"


//�ގ��̐F
static GLfloat ambColor[4] = { 0.6f, 0.6f, 0.6f, 1.0f }; 
static GLfloat diffColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
static GLfloat specColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
static GLfloat shiness = 30.0f;

//��������
/*struct Light
{
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat position[4];

	// �V�F�[�_�[�\�[�X�ł̏ꏊ
	GLint pl;         // �����ʒu�� uniform �ϐ��̏ꏊ
	GLint lamb;       // �������x�̊��������� uniform �ϐ��̏ꏊ
	GLint ldiff;      // �������x�̊g�U���ˌ������� uniform �ϐ��̏ꏊ
	GLint lspec;      // �������x�̋��ʔ��ˌ������� uniform �ϐ��̏ꏊ
};*/

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

	// �B�ʏ�����L���ɂ���
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// �A���t�@�u�����f�B���O�̐ݒ�
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//�r���[�|�[�g�ݒ�
	//glViewport(100, 50, 300, 300);

	//version3.2 core profile��I��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Draw(){

}

int main(){
	//GLFW�̏�����
	if (!Initialize_GLFW()){
		return 1;
	}

	//�E�C���h�E���쐬����
	Window::CreateWindow(1024, 768, "Test!");

	//GLEW�̏�����
	if (!Initialize_GLEW()){
		return 1;
	}

	//�����ݒ�
	InitConfig();
	InputManager::SetMyWindow(Window::GetWindow());
	if (!SeaquenceController::instance()){
		SeaquenceController::Create();
	}

	//TODO:�O���t�B�b�N�n�ɂ���
	//�g�p����V�F�[�_�[�̗p��
	Shader simple("lambert.vert", "lambert.frag");

	//���f���ǂݍ���
	//Model* m_bunny = new Model("bunny.obj");
	//���f���ɑ΂���}�e���A���̐ݒ�(�ގ��ݒ�+�ǂ̃V�F�[�_�[���g����)
	//m_bunny->MaterialSet(simple);

	// �E�B���h�E�S�̂��r���[�|�[�g�ɂ���
	glViewport(0, 0, Window::Get_w(), Window::Get_h());

	//�J���[�}�X�N�̐ݒ�
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	//�`�揈��
	while (Window::ShouldClose() == GL_FALSE){
		// ��ʏ���
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//�V�[�P���X�����̃`�F�b�N
		SeaquenceController::instance()->Update();

		//�V�F�[�_�̎g�p
		//m_bunny->GetMaterial()->m_shader->Use();
		//m_bunny->GetMaterial()->m_shader->loadMatrix(Window::getMp(), Window::ReturnMV()*Translate(0.0f, 0.0f, -2.0f));

		//�`��
		//m_bunny->Draw();
		// �V�F�[�_�v���O�����̎g�p�I��
		glUseProgram(0);
		//�o�b�t�@�����ւ���
		Window::SwapBuffers();

	}

	//�I��������̏���
	atexit(Cleanup);
	return 0;
}