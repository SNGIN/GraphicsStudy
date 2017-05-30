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

// ���̃f�[�^�̕�����
#define SLICES 64
#define STACKS 32

// ���̃f�[�^�̒��_���Ɩʐ�
#define VERTICES ((SLICES + 1) * (STACKS + 1))
#define FACES (SLICES * STACKS * 2)

//
// ���̃f�[�^�̍쐬
//
static void makeSphere(float radius, int slices, int stacks,
	GLfloat(*pv)[3], GLfloat(*nv)[3], GLfloat(*tv)[2], GLuint(*f)[3])
{
	// ���_�̈ʒu�ƃe�N�X�`�����W�����߂�
	for (int k = 0, j = 0; j <= stacks; ++j)
	{
		float t = (float)j / (float)stacks;
		float ph = 3.141593f * t;
		float y = cosf(ph);
		float r = sinf(ph);

		for (int i = 0; i <= slices; ++i)
		{
			float s = (float)i / (float)slices;
			float th = -2.0f * 3.141593f * s;
			float x = r * cosf(th);
			float z = r * sinf(th);

			// ���_�̍��W�l
			pv[k][0] = x * radius;
			pv[k][1] = y * radius;
			pv[k][2] = z * radius;

			// ���_�̖@���x�N�g��
			nv[k][0] = x;
			nv[k][1] = y;
			nv[k][2] = z;

			// ���_�̃e�N�X�`�����W�l
			tv[k][0] = s;
			tv[k][1] = t;

			++k;
		}
	}

	// �ʂ̎w�W�����߂�
	for (int k = 0, j = 0; j < stacks; ++j)
	{
		for (int i = 0; i < slices; ++i)
		{
			int count = (slices + 1) * j + i;

			// �㔼���̎O�p�`
			f[k][0] = count;
			f[k][1] = count + slices + 2;
			f[k][2] = count + 1;
			++k;

			// �������̎O�p�`
			f[k][0] = count;
			f[k][1] = count + slices + 1;
			f[k][2] = count + slices + 2;
			++k;
		}
	}
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

		// �V�F�[�_�v���O�����̎g�p�I��
		glUseProgram(0);
		//�o�b�t�@�����ւ���
		Window::SwapBuffers();

	}

	//�I��������̏���
	atexit(Cleanup);
	return 0;
}