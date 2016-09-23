#include "Model.h"

// �x�N�g��
struct vec
{
	float x, y, z;
};

bool Model::FileLoad(const char *name, GLuint &nv, GLfloat(*&pos)[3], GLfloat(*&norm)[3],
	GLuint &nf, GLuint(*&face)[3], bool normalize){
	//OBJ�t�@�C���ǂݍ���
	std::ifstream file(name, std::ios::binary);

	// �t�@�C�����J���Ȃ�������߂�
	if (file.fail())
	{
		std::cerr << "Error: Can't open OBJ file: " << name << std::endl;
		return false;
	}

	// ��s�ǂݍ��ݗp�̃o�b�t�@
	std::string line;

	// �f�[�^�̐��ƍ��W�l�̍ŏ��l�E�ő�l
	float xmin, xmax, ymin, ymax, zmin, zmax;
	xmax = ymax = zmax = -(xmin = ymin = zmin = FLT_MAX);

	// ���_�ʒu�̈ꎞ�ۑ�
	std::vector<vec> _pos;
	std::vector<faceData> _face;

	// �f�[�^��ǂݍ���
	while (std::getline(file, line))
	{
		std::istringstream str(line);
		std::string op;
		str >> op;

		

		if (op == "v")
		{
			// ���_�ʒu
			vec v;

			// ���_�ʒu�̓X�y�[�X�ŋ�؂��Ă���̂�
			str >> v.x >> v.y >> v.z;

			// �ʒu�̍ő�l�ƍŏ��l�����߂� (AABB)
			xmin = std::min(xmin, v.x);
			xmax = std::max(xmax, v.x);
			ymin = std::min(ymin, v.y);
			ymax = std::max(ymax, v.y);
			zmin = std::min(zmin, v.z);
			zmax = std::max(zmax, v.z);

			// ���_�f�[�^��ۑ�����
			_pos.push_back(v);
		}
		else if (op == "f")
		{
			// �ʃf�[�^
			faceData f;

			// ���_���W�ԍ������o��
			for (int i = 0; i < 3; ++i)
			{
				// 1�s���X�y�[�X�ŋ�؂��ČX�̗v�f�̍ŏ��̐��l�����o��
				std::string s;
				str >> s;
				f.p[i] = atoi(s.c_str());
			}

			//std::cout << vx << " " << vy << " " << vz << std::endl;

			// �ʃf�[�^��ۑ�����
			_face.push_back(f);
		}
		
	}

	// �t�@�C���̓ǂݍ��݃`�F�b�N
	if (file.bad())
	{
		// ���܂��ǂݍ��߂Ȃ�����
		std::cerr << "Warning: Can't read OBJ file: " << name << std::endl;
	}
	file.close();

	// �������̊m��
	pos = norm = NULL;
	face = NULL;
	nv = _pos.size();
	nf = _face.size();
	try
	{
		pos = new GLfloat[nv][3];
		norm = new GLfloat[nv][3];
		face = new GLuint[nf][3];
	}
	catch (std::bad_alloc e)
	{
		delete[] pos;
		delete[] norm;
		delete[] face;

		pos = norm = NULL;
		face = NULL;

		return false;
	}

	// �ʒu�Ƒ傫���̐��K���̂��߂̌W��
	GLfloat scale, cx, cy, cz;
	if (normalize)
	{
		const float sx(xmax - xmin);
		const float sy(ymax - ymin);
		const float sz(zmax - zmin);

		scale = sx;
		if (sy > scale) scale = sy;
		if (sz > scale) scale = sz;
		scale = (scale != 0.0f) ? 2.0f / scale : 1.0f;

		cx = (xmax + xmin) * 0.5f;
		cy = (ymax + ymin) * 0.5f;
		cz = (zmax + zmin) * 0.5f;
	}
	else
	{
		scale = 1.0f;
		cx = cy = cz = 0.0f;
	}

	// �}�`�̑傫���ƈʒu�̐��K���ƃf�[�^�̃R�s�[
	for (std::vector<vec>::const_iterator it = _pos.begin(); it != _pos.end(); ++it)
	{
		const size_t v = it - _pos.begin();

		pos[v][0] = (it->x - cx) * scale;
		pos[v][1] = (it->y - cy) * scale;
		pos[v][2] = (it->z - cz) * scale;
	}

	// ���_�@���̒l�� 0 �ɂ��Ă���
	std::fill(static_cast<GLfloat *>(&norm[0][0]), static_cast<GLfloat *>(&norm[nv][0]), 0.0f);

	// �ʂ̖@���̎Z�o�ƃf�[�^�̃R�s�[
	for (std::vector<faceData>::const_iterator it = _face.begin(); it != _face.end(); ++it)
	{
		const size_t f(it - _face.begin());

		// ���_���W�ԍ������o��
		const GLuint v0(face[f][0] = it->p[0] - 1);
		const GLuint v1(face[f][1] = it->p[1] - 1);
		const GLuint v2(face[f][2] = it->p[2] - 1);

		// v1 - v0, v2 - v0 �����߂�
		const GLfloat dx1(pos[v1][0] - pos[v0][0]);
		const GLfloat dy1(pos[v1][1] - pos[v0][1]);
		const GLfloat dz1(pos[v1][2] - pos[v0][2]);
		const GLfloat dx2(pos[v2][0] - pos[v0][0]);
		const GLfloat dy2(pos[v2][1] - pos[v0][1]);
		const GLfloat dz2(pos[v2][2] - pos[v0][2]);

		// �O�ςɂ��ʖ@�������߂�
		const GLfloat nx(dy1 * dz2 - dz1 * dy2);
		const GLfloat ny(dz1 * dx2 - dx1 * dz2);
		const GLfloat nz(dx1 * dy2 - dy1 * dx2);

		// �ʖ@���𒸓_�@���ɐώZ����
		norm[v0][0] += nx;
		norm[v0][1] += ny;
		norm[v0][2] += nz;
		norm[v1][0] += nx;
		norm[v1][1] += ny;
		norm[v1][2] += nz;
		norm[v2][0] += nx;
		norm[v2][1] += ny;
		norm[v2][2] += nz;
	}

	// ���_�@���̐��K��
	for (GLuint v = 0; v < nv; ++v)
	{
		// ���_�@���̒���
		GLfloat a(sqrt(norm[v][0] * norm[v][0] + norm[v][1] * norm[v][1] + norm[v][2] * norm[v][2]));

		// ���_�@���̐��K��
		if (a != 0.0)
		{
			norm[v][0] /= a;
			norm[v][1] /= a;
			norm[v][2] /= a;
		}
	}

	return true;
}

Model::Model()
{
}

//���f����ǂ݂���Ń��b�V���f�[�^�������o�Ƀ|�C���^�Ƃ��ĕێ�
Model::Model(const char *name, bool normalize){
	GLuint nv, nf;
	GLfloat(*pos)[3], (*norm)[3];
	GLuint(*face)[3];

	if (FileLoad(name, nv, pos, norm, nf, face, normalize)){
		m_Elements = new ShapeElements(nv, pos, norm, nf, face, GL_TRIANGLES);
		// ��Ɨp�Ɏg�������������������
		delete[] pos;
		delete[] norm;
		delete[] face;
	}
	else{
		std::cout << "Model Open Error" << std::endl;
	}
}


Model::~Model()
{
}

void Model::Draw(){
	//�V�F�[�_�̎g�p
	m_Material->m_shader->Use();
	//�`��
	m_Elements->Draw();
}

void Model::MaterialSet(GLfloat(*amb), GLfloat(*diff), GLfloat(*spec), GLfloat *shi, Shader &shader){
	m_Material = new Material(amb, diff, spec, shi,shader);
}