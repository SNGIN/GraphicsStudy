#pragma once

#include "Window.h"
#include "Shader.h"
#include "Model.h"

// �`��f�[�^
struct Object
{
	// ���_�z��I�u�W�F�N�g��
	GLuint vao;
	// �f�[�^�̗v�f��
	GLsizei count;
};

static GLfloat ambColor[4] = { 0.2f, 0.2f, 0.8f, 1.0f }; 
static GLfloat diffColor[4] = { 0.2f, 0.2f, 0.8f, 1.0f };
static GLfloat specColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat shiness = 30.0f;

const Matrix mv(Lookat(0.0f, 8.0f, 16.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f));


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
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	//�r���[�|�[�g�ݒ�
	//glViewport(100, 50, 300, 300);

	//version3.2 core profile��I��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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
	Window window1(1200, 1200, "hello!");

	//GLEW�̏�����
	if (!Initialize_GLEW()){
		return 1;
	}

	//������F�Ȃǂ̏����ݒ�
	InitConfig();

	//�g�p����V�F�[�_�[�̗p��
	Shader simple("lambert.vert", "lambert.frag");
	//���f���ǂݍ���
	Model m_bunny("bunny.obj",true);
	//���f���ɑ΂���}�e���A���̐ݒ�(�ގ��ݒ�+�ǂ̃V�F�[�_�[���g����)
	m_bunny.MaterialSet(ambColor, diffColor, specColor, &shiness, simple);

	// �E�B���h�E�S�̂��r���[�|�[�g�ɂ���
	glViewport(0, 0, window1.Get_w(), window1.Get_h());

	//�J���[�}�X�N�̐ݒ�
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	//�`�揈��
	while (window1.ShouldClose() == GL_FALSE){
		// �E�B���h�E����������
		glClear(GL_COLOR_BUFFER_BIT);

		//�z�u
		m_bunny.GetMaterial()->m_shader->loadMatrix(window1.getMp(),mv*Translate(0.0f,0.0f,0.0f));

		//�`��
		m_bunny.Draw();

		//�o�b�t�@�����ւ���
		window1.SwapBuffers();
	}

	//�Q�[�����I��������̏���
	atexit(Cleanup);
	return 0;
}