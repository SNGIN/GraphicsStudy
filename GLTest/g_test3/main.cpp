#include "Window.h";

static void Cleanup(void){
	//GLFW�̏I������
	glfwTerminate();
}

//������
static bool Initialize(){
	bool result = true;
	
	//GLFW������
	if (glfwInit() == GL_FALSE){
		//���������s
		std::cout << "GLFW Init not" << std::endl;
		result = false;
	}

	//glew�̏�����
	glewExperimental = GL_TRUE;
	if (glfwInit() == GL_FALSE){
		//���s
		std::cerr << "GLFW Init not" << std::endl;
		result = false;
	
	}
	return result;
}

// �����ݒ�
void InitConfig()
{
}

void Draw(){

}


int main(){
	//���������s
	if (!Initialize()){
		return 1;
	}

	//�E�C���h�E���쐬����
	Window window1(1200, 1200, "hello!");

	//�`�揈��
	while (window1.ShouldClose() == GL_FALSE){

		//�o�b�t�@�����ւ���
		window1.SwapBuffers();
	}


	
	//�Q�[�����I��������̏���
	atexit(Cleanup);
	return 0;
}