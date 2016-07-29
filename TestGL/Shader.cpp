#include "Shader.h"

static GLchar *readShaderSource(const char *name){
	//�t�@�C������NULL�Ȃ�NULL��Ԃ�
	if (name == NULL)return NULL;

	// �\�[�X�t�@�C�����J��
	std::ifstream file(name, std::ios::binary);
	if (file.fail())
	{
		// �J���Ȃ�����
		std::cerr << "Error: Can't open source file: " << name << std::endl;
		return NULL;
	}

	// �t�@�C���̖����Ɉړ����t�@�C���T�C�Y�𓾂�
	file.seekg(0L, std::ios::end);
	GLsizei length(static_cast<GLsizei>(file.tellg()));


	// �t�@�C���T�C�Y�̃��������m��
	GLchar *buffer(new(std::nothrow) GLchar[length + 1]);
	if (buffer == NULL)
	{
		// �������s��
		std::cerr << "Error: Too large file: " << name << std::endl;
		file.close();
		return NULL;
	}

	// �t�@�C����擪����ǂݍ���
	file.seekg(0L, std::ios::beg);
	file.read(buffer, length);
	buffer[length] = '\0';

	if (file.bad())
	{
		// ���܂��ǂݍ��߂Ȃ�����
		std::cerr << "Error: Could not read souce file: " << name << std::endl;
		delete buffer;
		buffer = NULL;
	}
	file.close();

	// �ǂݍ��񂾃\�[�X�v���O����
	return buffer;
}

static GLboolean printShaderInfoLog(GLuint shader, const char *str)
{
	// �R���p�C�����ʂ��擾����
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) std::cerr << "Compile Error in " << str << std::endl;

	// �V�F�[�_�̃R���p�C�����̃��O�̒������擾����
	GLsizei bufSize;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufSize);

	if (bufSize > 1)
	{
		// �V�F�[�_�̃R���p�C�����̃��O�̓��e���擾����
		std::vector<GLchar> infoLog(bufSize);
		GLsizei length;
		glGetShaderInfoLog(shader, bufSize, &length, &infoLog[0]);
		std::cerr << &infoLog[0] << std::endl;
	}
	return static_cast<GLboolean>(status);
}

static GLboolean printProgramInfoLog(GLuint program)
{
	// �����N���ʂ��擾����
	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) std::cerr << "Link Error." << std::endl;

	// �V�F�[�_�̃����N���̃��O�̒������擾����
	GLsizei bufSize;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufSize);

	if (bufSize > 1)
	{
		// �V�F�[�_�̃����N���̃��O�̓��e���擾����
		std::vector<GLchar> infoLog(bufSize);
		GLsizei length;
		glGetProgramInfoLog(program, bufSize, &length, &infoLog[0]);
		std::cerr << &infoLog[0] << std::endl;
	}

	return static_cast<GLboolean>(status);
}
GLuint createProgram(const char *vsrc, const char *pv, const char *fsrc, const char *fc,
	const char *vert, const char *frag){

	//��̃v���O�����I�u�W�F�N�g
	GLuint program = glCreateProgram();

	if (vsrc != NULL){
		//�o�[�e�b�N�X�V�F�[�_�I�u�W�F�N�g�̍쐬
		const GLuint vobj(glCreateShader(GL_VERTEX_SHADER));
		glShaderSource(vobj, 1, &vsrc, NULL);
		glCompileShader(vobj);
		
		//�o�[�e�b�N�X�V�F�[�_���A�^�b�`
		if (printShaderInfoLog(vobj, vert)){
			glAttachShader(program, vobj);
		}
		glDeleteShader(vobj);
	}

	if (fsrc != NULL){
		//�o�[�e�b�N�X�V�F�[�_�I�u�W�F�N�g�̍쐬
		const GLuint fobj(glCreateShader(GL_FRAGMENT_SHADER));
		glShaderSource(fobj, 1, &fsrc, NULL);
		glCompileShader(fobj);

		//�o�[�e�b�N�X�V�F�[�_���A�^�b�`
		if (printShaderInfoLog(fobj, frag)){
			glAttachShader(program, fobj);
		}
		glDeleteShader(fobj);
	}

	//�v���O�����I�u�W�F�N�g�̃����N
	glBindAttribLocation(program, 0, pv);
	glBindFragDataLocation(program, 0, fc);
	glLinkProgram(program);

	//�쐬�����v���O�����I�u�W�F�N�g��Ԃ�
	if (printProgramInfoLog(program)){
		return program;
	}
	else{
		glDeleteProgram(program);
		return 0;
	}
}

GLuint loadProgram(const char *vert, const char *pv, const char *frag, const char *fc)
{
	// �V�F�[�_�̃\�[�X�t�@�C����ǂݍ���
	const GLchar *vsrc(readShaderSource(vert));
	const GLchar *fsrc(readShaderSource(frag));

	// �v���O�����I�u�W�F�N�g���쐬����
	const GLuint program(createProgram(vsrc, pv, fsrc, fc));

	// �ǂݍ��݂Ɏg�������������������
	delete vsrc;
	delete fsrc;

	// �쐬�����v���O�����I�u�W�F�N�g��Ԃ�
	return program;
}