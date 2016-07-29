#include "Window.h"
#include "Shader.h";

// �`��f�[�^
struct Object
{
	// ���_�z��I�u�W�F�N�g��
	GLuint vao;
	// �f�[�^�̗v�f��
	GLsizei count;
};

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

// ���_�z��I�u�W�F�N�g�̍쐬
// vertices: ���_�̐�
// position: ���_�̈ʒu���i�[�����z��
GLuint createObject(GLuint vertices, const GLfloat(*position)[2])
{
	// ���_�z��I�u�W�F�N�g
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	// ���_�o�b�t�@�I�u�W�F�N�g
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof (GLfloat)* 2 * vertices, position, GL_STATIC_DRAW);
	// ��������Ă��钸�_�o�b�t�@�I�u�W�F�N�g�� in �ϐ�����Q�Ƃł���悤�ɂ���
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	// ���_�z��I�u�W�F�N�g�̌�������������
	glBindVertexArray(0);
	// ���_�o�b�t�@�I�u�W�F�N�g�̌�������������
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return vao;
}

// ��`�̃f�[�^���쐬����
Object createRectangle()
{
	// ���_�̈ʒu�f�[�^
	static const GLfloat position[][2] =
	{
		{ 0.5f, -0.5f },//0
		{ -0.5f, -0.5f },//1
		{ 0.5f, 0.5f },//2
		{ -0.5f, 0.5f }//3
	};
	// ���_�̐�
	static const int vertices(sizeof position / sizeof position[0]);
	// ���_�z��I�u�W�F�N�g�̍쐬
	Object object;

	object.vao = createObject(vertices, position);
	object.count = vertices;
	return object;
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

	// �v���O�����I�u�W�F�N�g�̍쐬
	const GLuint program(loadProgram("point.vert", "pv", "point.frag", "fc"));

	InitConfig();

	const Object object(createRectangle());

	//�`�揈��
	while (window1.ShouldClose() == GL_FALSE){
		// �E�B���h�E����������
		glClear(GL_COLOR_BUFFER_BIT);
		//�V�F�[�_�v���O�����̓K�p
		glUseProgram(program);

		glBindVertexArray(object.vao);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, object.count);

		//�o�b�t�@�����ւ���
		window1.SwapBuffers();
	}

	//�Q�[�����I��������̏���
	atexit(Cleanup);
	return 0;
}