#include "Texture.h"


Texture::Texture()
{
	//�e�N�X�`���I�u�W�F�N�g�����
	glGenTextures(1, &texture);
}

Texture::Texture(GLuint tex):texture(tex){}

/*Texture::Texture(GLsizei width, GLsizei height, GLenum internal = GL_RGBA, GLenum format = GL_RGBA, const GLubyte *image = 0){
	//�n���ꂽ�|�C���^���g���ăe�N�X�`���������֓ǂݍ���

	//�e�N�X�`���I�u�W�F�N�g�����
	glGenTextures(1, &texture);
	//2D�e�N�X�`���Ƃ��Ďg�p����錾
	glBindTexture(GL_TEXTURE_2D, texture);
	//�e�N�X�`���̃��[�h
	LoadTexture(width, height, internal, format, image);
}*/

Texture::Texture(char *name, GLenum internal = GL_RGBA){
	//�w�肵�����O�t�@�C�����e�N�X�`���������֓ǂݍ���

	//�e�N�X�`���I�u�W�F�N�g�����
	glGenTextures(1, &texture);
	//2D�e�N�X�`���Ƃ��Ďg�p����錾
	glBindTexture(GL_TEXTURE_2D, texture);
	//�e�N�X�`���̓ǂݍ���
	LoadImage(name, internal);
}

//tga�t�@�C�����������ɓǂ�
GLuint Texture::LoadImage(const char *name, GLenum internal){
	GLsizei width, height;
	GLenum format;

	const GLubyte* image = LoadTGA(name, &width, &height, &format);
	if (image == NULL)return 0;
	// internal == 0 �Ȃ�����t�H�[�}�b�g��ǂݍ��񂾃t�@�C���ɍ��킹��
	if (internal == 0)
	{
		switch (format)
		{
		case GL_BGR:
			internal = GL_RGB;
			break;
		case GL_BGRA:
			internal = GL_RGBA;
			break;
		default:
			internal = format;
			break;
		}
	}

	// �e�N�X�`���������ɓǂݍ���
	const GLuint tex(LoadTexture(width, height, internal, format, image));

	// �摜�̓ǂݍ��݂Ɏg�������������������
	delete[] image;

	// �e�N�X�`���I�u�W�F�N�g����Ԃ�
	return tex;
}

//tga�t�@�C����ǂ�
GLubyte* Texture::LoadTGA(const char *name, GLsizei *width, GLsizei *height, GLenum *format){
	// �t�@�C�����J��
	std::ifstream file(name, std::ios::binary);

	// �t�@�C�����J���Ȃ�������߂�
	if (file.fail())
	{
		std::cerr << "Waring: Can't open file: " << name << std::endl;
		return NULL;
	}

	// �w�b�_��ǂݍ���(tga�̃w�b�_����18�o�C�g)
	unsigned char header[18];
	file.read(reinterpret_cast<char *>(header), sizeof header);

	// �w�b�_�̓ǂݍ��݂Ɏ��s������߂�
	if (file.bad())
	{
		std::cerr << "Waring: Can't read file header: " << name << std::endl;
		file.close();
		return NULL;
	}

	// ���ƍ���
	*width = header[13] << 8 | header[12];
	*height = header[15] << 8 | header[14];

	// �[�x
	const size_t depth(header[16] / 8);
	switch (depth)
	{
	case 1:
		*format = GL_RED;
		break;
	case 2:
		*format = GL_RG;
		break;
	case 3:
		*format = GL_BGR;
		break;
	case 4:
		*format = GL_BGRA;
		break;
	default:
		// ��舵���Ȃ��t�H�[�}�b�g��������߂�
		std::cerr << "Waring: Unusable format: " << depth << std::endl;
		file.close();
		return NULL;
	}

	// �f�[�^�T�C�Y
	const size_t size(*width * *height * depth);

	// �ǂݍ��݂Ɏg�����������m�ۂ���
	GLubyte *const buffer(new(std::nothrow) GLubyte[size]);

	// ���������m�ۂł��Ȃ���Ζ߂�
	if (buffer == NULL)
	{
		std::cerr << "Waring: Too large file: " << name << std::endl;
		file.close();
		return NULL;
	}

	// �f�[�^��ǂݍ���
	if (header[2] & 8)
	{
		// RLE
		size_t p(0);
		char c;
		while (file.get(c))
		{
			if (c & 0x80)
			{
				// run-length packet
				//TODO:�������K�v
				const size_t count((c & 0x7f) + 1);
				if (p + count * depth > size) break;
				char tmp[4];
				file.read(tmp, depth);
				for (size_t i = 0; i < count; ++i)
				{
					for (size_t j = 0; j < depth;) buffer[p++] = tmp[j++];
				}
			}
			else
			{
				// raw packet
				const size_t count((c + 1) * depth);
				if (p + count > size) break;
				file.read(reinterpret_cast<char *>(buffer + p), count);
				p += count;
			}
		}
	}
	else
	{
		// �񈳏k
		file.read(reinterpret_cast<char *>(buffer), size);
	}

	// �ǂݍ��݂Ɏ��s���Ă�����x�����o��
	if (file.bad())
	{
		std::cerr << "Waring: Can't read image data: " << name << std::endl;
	}
	// �t�@�C�������
	file.close();

	// �摜��ǂݍ��񂾃�������Ԃ�
	return buffer;
}

//�R�Â���؂��ăe�N�X�`�������
Texture::~Texture()
{
	if (last()){
		glBindTexture(GL_TEXTURE_2D, 0);
		glDeleteTextures(1, &texture);
	}
}

//�g���e�N�X�`���̐錾
void Texture::Use(GLuint loc,GLuint unit=0)const{
	glUniform1i(loc, 0);
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, texture);
}

//�e�N�X�`���̊J��
void Texture::Release()const{
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);
}

//�e�N�X�`���̎擾
GLuint Texture::Get()const{
	return texture;
}

//�e�N�X�`���̃��[�h
GLuint Texture::LoadTexture(GLsizei width, GLsizei height, GLenum internal, GLenum format, const GLubyte *image){
	// �A���t�@�`�����l�������Ă���� 4 �o�C�g���E�ɐݒ肷��
	glPixelStorei(GL_UNPACK_ALIGNMENT, (format == GL_BGRA || format == GL_RGBA) ? 4 : 1);

	// �e�N�X�`�������蓖�Ă�
	glTexImage2D(GL_TEXTURE_2D, 0, internal, width, height, 0, format, GL_UNSIGNED_BYTE, image);

	// �o�C���j�A�i�~�b�v�}�b�v�Ȃ��j�C�G�b�W�ŃN�����v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	return texture;
}

//TODO:��`�N���X�����(�����o�[�Ƀe�N�X�`���N���X�A�V�F�[�_�[���炷�����l�p�`�I�u�W�F�N���X)