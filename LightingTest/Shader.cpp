#include "Shader.h"

static GLchar *ReadShaderSource(const char *name){
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

	// �ǂݍ��񂾃\�[�X�v���O�����̃�����
	return buffer;
}

GLuint CreateShader(const char *vsrc, const char *fsrc, const char *gsrc,
	GLint nvarying, const char **varyings, const char *vtext, const char *ftext, const char *gtext){

	//��̃v���O�����I�u�W�F�N�g
	const GLuint program(glCreateProgram());

	if (program > 0){
		if (vsrc != NULL){
			//�o�[�e�b�N�X�V�F�[�_�I�u�W�F�N�g�̍쐬
			const GLuint vobj(glCreateShader(GL_VERTEX_SHADER));
			glShaderSource(vobj, 1, &vsrc, NULL);
			glCompileShader(vobj);

			//�o�[�e�b�N�X�V�F�[�_���A�^�b�`
			if (printShaderInfoLog(vobj, vtext)){
				glAttachShader(program, vobj);
			}
			glDeleteShader(vobj);
		}

		if (fsrc != NULL){
			//�t���O�����g�V�F�[�_�I�u�W�F�N�g�̍쐬
			const GLuint fobj(glCreateShader(GL_FRAGMENT_SHADER));
			glShaderSource(fobj, 1, &fsrc, NULL);
			glCompileShader(fobj);

			//�t���O�����g�V�F�[�_���A�^�b�`
			if (printShaderInfoLog(fobj, ftext)){
				glAttachShader(program, fobj);
			}
			glDeleteShader(fobj);
		}

		if (gsrc!=NULL)
		{
			// �W�I���g���V�F�[�_�̃V�F�[�_�I�u�W�F�N�g���쐬
			const GLuint geomShader(glCreateShader(GL_GEOMETRY_SHADER));
			glShaderSource(geomShader, 1, &gsrc, NULL);
			glCompileShader(geomShader);

			// �W�I���g���V�F�[�_�̃V�F�[�_�����^�b�`
			if (printShaderInfoLog(geomShader, gtext)){
				glAttachShader(program, geomShader);
			}
			glDeleteShader(geomShader);
		}

		if (nvarying > 0){
			glTransformFeedbackVaryings(program, nvarying, varyings, GL_SEPARATE_ATTRIBS);
		}

		//�v���O�����I�u�W�F�N�g�̃����N
		glLinkProgram(program);
	}

	//�쐬�����v���O�����I�u�W�F�N�g��Ԃ�
	if (printProgramInfoLog(program)){
		return program;
	}
	else{
		glDeleteProgram(program);
		return 0;
	}
}

GLuint LoadShader(const char *vert, const char *frag, const char *geom,
	GLint nvarying, const char **varyings){
	// �V�F�[�_�̃\�[�X�t�@�C����ǂݍ���
	const GLchar *const vsrc(ReadShaderSource(vert));
	const GLchar *const fsrc(ReadShaderSource(frag));
	const GLchar *const gsrc(ReadShaderSource(geom));

	// �v���O�����I�u�W�F�N�g���쐬����
	const GLuint program(CreateShader(vsrc, fsrc, gsrc, nvarying, varyings, vert, frag, geom));

	// �\�[�X�t�@�C���̓ǂݍ��݂Ɏg�������������������
	delete[] vsrc;
	delete[] fsrc;
	delete[] gsrc;

	// �쐬�����v���O�����I�u�W�F�N�g��Ԃ�
	return program;
}

void Shader::loadMatrix(const Matrix &mp, const Matrix &mw){
	// �ϊ�
	glUniformMatrix4fv(loc_matrix.mc, 1, GL_FALSE, (mp * mw).get());
	glUniformMatrix4fv(loc_matrix.mw, 1, GL_FALSE, mw.get());
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