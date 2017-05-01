#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "opengl32.lib")

#pragma once

#include "glew.h"
#include "glfw3.h"
#include <math.h>

class Matrix
{
	// �ϊ��s��̗v�f
	GLfloat array[16];

	// �s�� a �ƃx�N�g�� b �̐ς��x�N�g�� c �ɑ������
	void projection(GLfloat *c, const GLfloat *a, const GLfloat *b) const{
		for (int i = 0; i < 4; ++i)
		{
			c[i] = a[0 + i] * b[0] + a[4 + i] * b[1] + a[8 + i] * b[2] + a[12 + i] * b[3];
		}
	}

	// �s�� a �ƍs�� b �̐ς��s�� c �ɑ������
	void multiply(GLfloat *c, const GLfloat *a, const GLfloat *b) const{
		for (int i = 0; i < 16; ++i)
		{
			int j = i & 3, k = i & ~3;

			c[i] = a[0 + j] * b[k + 0] + a[4 + j] * b[k + 1] + a[8 + j] * b[k + 2] + a[12 + j] * b[k + 3];
		}
	}

public:

	//! \brief �f�X�g���N�^.
	virtual ~Matrix() {}

	//! \brief �R���X�g���N�^.
	Matrix() {}

	//! \brief �R���X�g���N�^.
	//!   \param a GLfloat[16] �^�̔z��.
	Matrix(const GLfloat *a)
	{
		load(a);
	}

	//! \brief �R�s�[�R���X�g���N�^.
	//!   \param m Matrix �^�̕ϐ�.
	Matrix(const Matrix &m)
	{
		load(m);
	}

	//! \brief �z��ϐ��̒l���i�[����.
	//!   \param a GLfloat[16] �^�̔z��.
	//!   \return a �������� Matrix �^�̒l.
	Matrix &load(const GLfloat *a)
	{
		for (int i = 0; i < 16; ++i) array[i] = a[i];
		return *this;
	}

	//! \brief �ʂ̕ϊ��s��̒l���i�[����.
	//!   \param m Matrix �^�̕ϐ�.
	//!   \return m �������� Matrix �^�̒l.
	Matrix &load(const Matrix &m)
	{
		return load(m.array);
	}

	//! \brief �ϊ��s��ɔz��Ɋi�[�����ϊ��s������Z�������ʂ��i�[����.
	//!   \param a GLfloat[16] �^�̔z��.
	//!   \return �ϊ��s��� a �������� Matrix �^�̒l.
	Matrix &loadAdd(const GLfloat *a)
	{
		for (int i = 0; i < 16; ++i) array[i] += a[i];
		return *this;
	}

	//! \brief �ϊ��s��ɕʂ̕ϊ��s������Z�������ʂ��i�[����.
	//!   \param m Matrix �^�̕ϐ�.
	//!   \return �ϊ��s��� m �������� Matrix �^�̒l.
	Matrix &loadAdd(const Matrix &m)
	{
		return loadAdd(m.array);
	}

	//! \brief �ϊ��s�񂩂�z��Ɋi�[�����ϊ��s������Z�������ʂ��i�[����.
	//!   \param a GLfloat[16] �^�̔z��.
	//!   \return �ϊ��s��� a �������� Matrix �^�̒l.
	Matrix &loadSubtract(const GLfloat *a)
	{
		for (int i = 0; i < 16; ++i) array[i] -= a[i];
		return *this;
	}

	//! \brief �ϊ��s�񂩂�ʂ̕ϊ��s������Z�������ʂ��i�[����.
	//!   \param m Matrix �^�̕ϐ�.
	//!   \return �ϊ��s��� m �������� Matrix �^�̒l.
	Matrix &loadSubtract(const Matrix &m)
	{
		return loadSubtract(m.array);
	}

	//! \brief �ϊ��s��ɔz��Ɋi�[�����ϊ��s�����Z�������ʂ��i�[����.
	//!   \param a GLfloat[16] �^�̔z��.
	//!   \return �ϊ��s��� a ���|���� Matrix �^�̒l.
	Matrix &loadMultiply(const GLfloat *a)
	{
		return load(multiply(a));
	}

	//! \brief �ϊ��s��ɕʂ̕ϊ��s�����Z�������ʂ��i�[����.
	//!   \param m Matrix �^�̕ϐ�.
	//!   \return �ϊ��s��� m ���|���� Matrix �^�̒l.
	Matrix &loadMultiply(const Matrix &m)
	{
		return loadMultiply(m.array);
	}

	//! \brief �ϊ��s���z��Ɋi�[�����ϊ��s��ŏ��Z�������ʂ��i�[����.
	//!   \param a GLfloat[16] �^�̔z��.
	//!   \return �ϊ��s��� a ���悶�� Matrix �^�̒l.
	Matrix &loadDivide(const GLfloat *a)
	{
		return load(divide(a));
	}

	//! \brief �ϊ��s���ʂ̕ϊ��s��ŏ��Z�������ʂ��i�[����.
	//!   \param m Matrix �^�̕ϐ�.
	//!   \return �ϊ��s��� m ���悶�� Matrix �^�̒l.
	Matrix &loadDivide(const Matrix &m)
	{
		return loadDivide(m.array);
	}

	//! \brief �ϊ��s��ɔz��Ɋi�[�����ϊ��s������Z�����l��Ԃ�.
	//!   \param a GLfloat[16] �^�̔z��.
	//!   \return �ϊ��s��� a �������� Matrix �^�̒l.
	Matrix add(const GLfloat *a) const
	{
		Matrix t;
		return t.loadAdd(a);
	}

	//! \brief �ϊ��s��ɕʂ̕ϊ��s������Z�����l��Ԃ�.
	//!   \param m Matrix �^�̕ϐ�.
	//!   \return �ϊ��s��� m �������� Matrix �^�̒l.
	Matrix add(const Matrix &m) const
	{
		return add(m.array);
	}

	//! \brief �ϊ��s�񂩂�z��Ɋi�[�����ϊ��s������Z�����l��Ԃ�.
	//!   \param a GLfloat[16] �^�̔z��.
	//!   \return �ϊ��s��� a �������� Matrix �^�̒l.
	Matrix subtract(const GLfloat *a) const
	{
		Matrix t;
		return t.loadSubtract(a);
	}

	//! \brief �ϊ��s�񂩂�ʂ̕ϊ��s������Z�����l��Ԃ�.
	//!   \param m Matrix �^�̕ϐ�.
	//!   \return �ϊ��s��� m �������� Matrix �^�̒l.
	Matrix subtract(const Matrix &m) const
	{
		return subtract(m.array);
	}

	//! \brief �ϊ��s��ɔz��Ɋi�[�����ϊ��s�����Z�����l��Ԃ�.
	//!   \param a GLfloat[16] �^�̔z��.
	//!   \return �ϊ��s��� a ���|���� Matrix �^�̒l.
	Matrix multiply(const GLfloat *a) const
	{
		Matrix t;
		multiply(t.array, array, a);
		return t;
	}
//!   \param m Matrix �^�̕ϐ�.
//!   \return �ϊ��s��� m ���|���� Matrix �^�̒l.
Matrix multiply(const Matrix &m) const
{
	return multiply(m.array);
}

//! \brief �ϊ��s���z��Ɋi�[�����ϊ��s��ŏ��Z�����l��Ԃ�.
//!   \param a GLfloat[16] �^�̔z��.
//!   \return �ϊ��s��� a �Ŋ����� Matrix �^�̒l.
Matrix divide(const GLfloat *a) const
{
	Matrix t, ia;
	ia.loadInvert(a);
	multiply(t.array, array, ia.array);
	return t;
}

//! \brief �ϊ��s���z��Ɋi�[�����ϊ��s��ŏ��Z�����l��Ԃ�.
//!   \param m Matrix �^�̕ϐ�.
//!   \return �ϊ��s��� m �Ŋ����� Matrix �^�̒l.
Matrix divide(const Matrix &m) const
{
	return divide(m.array);
}

// ���Z�q
Matrix &operator=(const GLfloat *a)
{
	return load(a);
}
Matrix &operator=(const Matrix &m)
{
	return operator=(m.array);
}
Matrix &operator+=(const GLfloat *a)
{
	return loadAdd(a);
}
Matrix &operator+=(const Matrix &m)
{
	return operator+=(m.array);
}
Matrix &operator-=(const GLfloat *a)
{
	return loadSubtract(a);
}
Matrix &operator-=(const Matrix &m)
{
	return operator-=(m.array);
}
Matrix &operator*=(const GLfloat *a)
{
	return loadMultiply(a);
}
Matrix &operator*=(const Matrix &m)
{
	return operator*=(m.array);
}
Matrix &operator/=(const GLfloat *a)
{
	return loadDivide(a);
}
Matrix &operator/=(const Matrix &m)
{
	return operator/=(m.array);
}
Matrix operator+(const GLfloat *a) const
{
	return add(a);
}
Matrix operator+(const Matrix &m) const
{
	return operator+(m.array);
}
Matrix operator-(const GLfloat *a) const
{
	return subtract(a);
}
Matrix operator-(const Matrix &m) const
{
	return operator-(m.array);
}
Matrix operator*(const GLfloat *a) const
{
	return multiply(a);
}
Matrix operator*(const Matrix &m) const
{
	return operator*(m.array);
}
Matrix operator/(const GLfloat *a) const
{
	return divide(a);
}
Matrix operator/(const Matrix &m) const
{
	return operator/(m.array);
}

//! \brief �P�ʍs����i�[����.
Matrix &loadIdentity();

//! \brief ���s�ړ��̕ϊ��s����i�[����.
//!   \param x x �����̈ړ���.
//!   \param y y �����̈ړ���.
//!   \param z z �����̈ړ���.
//!   \param w w �ړ��ʂ̃X�P�[���t�@�N�^ (= 1.0f).
//!   \return �ݒ肵���ϊ��s��.
Matrix &loadTranslate(GLfloat x, GLfloat y, GLfloat z, GLfloat w = 1.0f){
	array[12] = x;
	array[13] = y;
	array[14] = z;
	array[0] = array[5] = array[10] = array[15] = w;
	array[1] = array[2] = array[3] = array[4] =
		array[6] = array[7] = array[8] = array[9] =
		array[11] = 0.0f;

	return *this;
}

//! \brief ���s�ړ��̕ϊ��s����i�[����.
//!   \param t �ړ��ʂ� GLfloat[4] �^�̔z�� (x, y, z, w).
//!   \return �ݒ肵���ϊ��s��.
Matrix &loadTranslate(const GLfloat *t)
{
	return loadTranslate(t[0], t[1], t[2], t[3]);
}

//! \brief �g��k���̕ϊ��s����i�[����.
//!   \param x x �����̊g�嗦.
//!   \param y y �����̊g�嗦.
//!   \param z z �����̊g�嗦.
//!   \param w w �g�嗦�̃X�P�[���t�@�N�^ (= 1.0f).
//!   \return �ݒ肵���ϊ��s��.
Matrix &loadScale(GLfloat x, GLfloat y, GLfloat z, GLfloat w = 1.0f);

//! \brief �g��k���̕ϊ��s����i�[����.
//!   \param s �g�嗦�� GLfloat[4] �^�̔z�� (x, y, z, w).
//!   \return �ݒ肵���ϊ��s��.
Matrix &loadScale(const GLfloat *s)
{
	return loadScale(s[0], s[1], s[2], s[3]);
}

//! \brief x �����S�̉�]�̕ϊ��s����i�[����.
//!   \param a ��]�p.
//!   \return �ݒ肵���ϊ��s��.
Matrix &loadRotateX(GLfloat a){
	GLfloat c = cos(a);
	GLfloat s = sin(a);

	array[0] = 1.0f; array[1] = 0.0f; array[2] = 0.0f; array[3] = 0.0f;
	array[4] = 0.0f; array[5] = c;    array[6] = s;    array[7] = 0.0f;
	array[8] = 0.0f; array[9] = -s;   array[10] = c;    array[11] = 0.0f;
	array[12] = 0.0f; array[13] = 0.0f; array[14] = 0.0f; array[15] = 1.0f;

	return *this;
}

//! \brief y �����S�̉�]�̕ϊ��s����i�[����.
//!   \param a ��]�p.
//!   \return �ݒ肵���ϊ��s��.
Matrix &loadRotateY(GLfloat a);

//! \brief z �����S�̉�]�̕ϊ��s����i�[����.
//!   \param a ��]�p.
//!   \return �ݒ肵���ϊ��s��.
Matrix &loadRotateZ(GLfloat a);

//! \brief (x, y, z) �����̃x�N�g�������Ƃ����]�̕ϊ��s����i�[����.
//!   \param x ��]���� x ����.
//!   \param y ��]���� y ����.
//!   \param z ��]���� z ����.
//!   \param a ��]�p.
//!   \return �ݒ肵���ϊ��s��.
Matrix &loadRotate(GLfloat x, GLfloat y, GLfloat z, GLfloat a);

//! \brief r �����̃x�N�g�������Ƃ����]�̕ϊ��s����i�[����.
//!   \param r ��]���̕����x�N�g�� (x, y, z).
//!   \param a ��]�p.
//!   \return �ݒ肵���ϊ��s��.
Matrix &loadRotate(const GLfloat *r, GLfloat a)
{
	return loadRotate(r[0], r[1], r[2], a);
}

//! \brief r �����̃x�N�g�������Ƃ����]�̕ϊ��s����i�[����.
//!   \param r ��]���̕����x�N�g���Ɖ�]�p (x, y, z, a).
//!   \return �ݒ肵���ϊ��s��.
Matrix &loadRotate(const GLfloat *r)
{
	return loadRotate(r[0], r[1], r[2], r[3]);
}

//! \brief �r���[�ϊ��s����i�[����.
//!   \param ex ���_�̈ʒu�� x ���W�l.
//!   \param ey ���_�̈ʒu�� y ���W�l.
//!   \param ez ���_�̈ʒu�� z ���W�l.
//!   \param tx �ڕW�_�̈ʒu�� x ���W�l.
//!   \param ty �ڕW�_�̈ʒu�� y ���W�l.
//!   \param tz �ڕW�_�̈ʒu�� z ���W�l.
//!   \param ux ������̃x�N�g���� x ����.
//!   \param uy ������̃x�N�g���� y ����.
//!   \param uz ������̃x�N�g���� z ����.
//!   \return �ݒ肵���r���[�ϊ��s��.
Matrix &loadLookat(GLfloat ex, GLfloat ey, GLfloat ez,
	GLfloat tx, GLfloat ty, GLfloat tz,
	GLfloat ux, GLfloat uy, GLfloat uz){
	// z �� = e - t
	GLfloat zx = ex - tx;
	GLfloat zy = ey - ty;
	GLfloat zz = ez - tz;
	const GLfloat zl = sqrt(zx * zx + zy * zy + zz * zz);
	if (zl == 0.0f) return *this;

	// z ���̐��K��
	zx /= zl;
	zy /= zl;
	zz /= zl;

	// x �� = u x z ��
	GLfloat xx = uy * zz - uz * zy;
	GLfloat xy = uz * zx - ux * zz;
	GLfloat xz = ux * zy - uy * zx;
	const GLfloat xl = sqrt(xx * xx + xy * xy + xz * xz);
	if (xl == 0.0f) return *this;

	// x ���̐��K��
	xx /= xl;
	xy /= xl;
	xz /= xl;

	// z ��
	array[2] = zx;
	array[6] = zy;
	array[10] = zz;

	// x ��
	array[0] = xx;
	array[4] = xy;
	array[8] = xz;

	// y �� = z �� x x ��
	array[1] = zy * xz - zz * xy;
	array[5] = zz * xx - zx * xz;
	array[9] = zx * xy - zy * xx;

	// ���s�ړ�
	array[12] = -(ex * array[0] + ey * array[4] + ez * array[8]);
	array[13] = -(ex * array[1] + ey * array[5] + ez * array[9]);
	array[14] = -(ex * array[2] + ey * array[6] + ez * array[10]);

	// �c��
	array[3] = array[7] = array[11] = 0.0f;
	array[15] = 1.0f;

	return *this;
}

//! \brief �r���[�ϊ��s����i�[����.
//!   \param e ���_�̈ʒu�̔z��ϐ�.
//!   \param t �ڕW�_�̈ʒu�̔z��ϐ�.
//!   \param u ������̃x�N�g���̂̔z��ϐ�.
//!   \return �ݒ肵���r���[�ϊ��s��.
Matrix &loadLookat(const GLfloat *e, const GLfloat *t, const GLfloat *u)
{
	return loadLookat(e[0], e[1], e[2], t[0], t[1], t[2], u[0], u[1], u[2]);
}

//! \brief ���𓊉e�ϊ��s����i�[����.
//!   \param left �E�B���h�E�̍��[�̈ʒu.
//!   \param right �E�B���h�E�̉E�[�̈ʒu.
//!   \param bottom �E�B���h�E�̉��[�̈ʒu.
//!   \param top �E�B���h�E�̏�[�̈ʒu.
//!   \param zNear ���_����O���ʂ܂ł̈ʒu.
//!   \param zFar ���_�������ʂ܂ł̈ʒu.
//!   \return �ݒ肵�����𓊉e�ϊ��s��.
Matrix &loadOrthogonal(GLfloat left, GLfloat right,
	GLfloat bottom, GLfloat top,
	GLfloat zNear, GLfloat zFar){
	const GLfloat dx(right - left);
	const GLfloat dy(top - bottom);
	const GLfloat dz(zFar - zNear);

	if (dx != 0.0f && dy != 0.0f && dz != 0.0f)
	{
		array[0] = 2.0f / dx;
		array[5] = 2.0f / dy;
		array[10] = -2.0f / dz;
		array[12] = -(right + left) / dx;
		array[13] = -(top + bottom) / dy;
		array[14] = -(zFar + zNear) / dz;
		array[15] = 1.0f;
		array[1] = array[2] = array[3] = array[4] =
			array[6] = array[7] = array[8] = array[9] =
			array[11] = 0.0f;
	}

	return *this;
}

//! \brief �����������e�ϊ��s����i�[����.
//!   \param left �E�B���h�E�̍��[�̈ʒu.
//!   \param right �E�B���h�E�̉E�[�̈ʒu.
//!   \param bottom �E�B���h�E�̉��[�̈ʒu.
//!   \param top �E�B���h�E�̏�[�̈ʒu.
//!   \param zNear ���_����O���ʂ܂ł̈ʒu.
//!   \param zFar ���_�������ʂ܂ł̈ʒu.
//!   \return �ݒ肵���������e�ϊ��s��.
Matrix &loadFrustum(GLfloat left, GLfloat right,
	GLfloat bottom, GLfloat top,
	GLfloat zNear, GLfloat zFar){
	const GLfloat dx(right - left);
	const GLfloat dy(top - bottom);
	const GLfloat dz(zFar - zNear);

	if (dx != 0.0f && dy != 0.0f && dz != 0.0f)
	{
		array[0] = 2.0f * zNear / dx;
		array[5] = 2.0f * zNear / dy;
		array[8] = (right + left) / dx;
		array[9] = (top + bottom) / dy;
		array[10] = -(zFar + zNear) / dz;
		array[11] = -1.0f;
		array[14] = -2.0f * zFar * zNear / dz;
		array[1] = array[2] = array[3] = array[4] =
			array[6] = array[7] = array[12] = array[13] =
			array[15] = 0.0f;
	}

	return *this;
}

//! \brief ��p���w�肵�ē������e�ϊ��s����i�[����.
//!   \param fovy y �����̉�p.
//!   \param aspect �c����.
//!   \param zNear ���_����O���ʂ܂ł̈ʒu.
//!   \param zFar ���_�������ʂ܂ł̈ʒu.
//!   \return �ݒ肵���������e�ϊ��s��.
Matrix &loadPerspective(GLfloat fovy, GLfloat aspect,
	GLfloat zNear, GLfloat zFar){
	const GLfloat dz(zFar - zNear);

	if (dz != 0.0f)
	{
		array[5] = 1.0f / tan(fovy * 0.5f);
		array[0] = array[5] / aspect;
		array[10] = -(zFar + zNear) / dz;
		array[11] = -1.0f;
		array[14] = -2.0f * zFar * zNear / dz;
		array[1] = array[2] = array[3] = array[4] =
			array[6] = array[7] = array[8] = array[9] =
			array[12] = array[13] = array[15] = 0.0f;
	}

	return *this;
}

//! \brief �]�u�s����i�[����.
//!   \param a GLfloat[16] �^�̕ϊ��s��.
//!   \return �ݒ肵�� a �̓]�u�s��.
Matrix &loadTranspose(const GLfloat *marray){
  array[ 0] = marray[ 0];
  array[ 1] = marray[ 4];
  array[ 2] = marray[ 8];
  array[ 3] = marray[12];
  array[ 4] = marray[ 1];
  array[ 5] = marray[ 5];
  array[ 6] = marray[ 9];
  array[ 7] = marray[13];
  array[ 8] = marray[ 2];
  array[ 9] = marray[ 6];
  array[10] = marray[10];
  array[11] = marray[14];
  array[12] = marray[ 3];
  array[13] = marray[ 7];
  array[14] = marray[11];
  array[15] = marray[15];

  return *this;
}

//! \brief �]�u�s����i�[����.
//!   \param m Matrix �^�̕ϊ��s��.
//!   \return �ݒ肵�� m �̓]�u�s��.
Matrix &loadTranspose(const Matrix &m)
{
	return loadTranspose(m.array);
}

//! \brief �t�s����i�[����.
//!   \param a GLfloat[16] �^�̕ϊ��s��.
//!   \return �ݒ肵�� a �̋t�s��.
Matrix &loadInvert(const GLfloat *a);

//! \brief �t�s����i�[����.
//!   \param m Matrix �^�̕ϊ��s��.
//!   \return �ݒ肵�� m �̋t�s��.
Matrix &loadInvert(const Matrix &m)
{
	return loadInvert(m.array);
}

//! \brief �@���ϊ��s����i�[����.
//!   \param a GLfloat[16] �^�̕ϊ��s��.
//!   \return �ݒ肵�� m �̖@���ϊ��s��.
Matrix &loadNormal(const GLfloat *marray){
	//�ϊ��s��F�@���ϊ��s���ݒ肷��

	array[0] = marray[5] * marray[10] - marray[6] * marray[9];
	array[1] = marray[6] * marray[8] - marray[4] * marray[10];
	array[2] = marray[4] * marray[9] - marray[5] * marray[8];
	array[4] = marray[9] * marray[2] - marray[10] * marray[1];
	array[5] = marray[10] * marray[0] - marray[8] * marray[2];
	array[6] = marray[8] * marray[1] - marray[9] * marray[0];
	array[8] = marray[1] * marray[6] - marray[2] * marray[5];
	array[9] = marray[2] * marray[4] - marray[0] * marray[6];
	array[10] = marray[0] * marray[5] - marray[1] * marray[4];
	array[3] = array[7] = array[11] = array[12] = array[13] = array[14] = 0.0f;
	array[15] = 1.0f;

	return *this;
		
}

//! \brief �@���ϊ��s����i�[����.
//!   \param Matrix �^�̕ϊ��s��.
//!   \return �ݒ肵�� m �̖@���ϊ��s��.
Matrix &loadNormal(const Matrix &m)
{
	return loadNormal(m.array);
}

//! \brief ���s�ړ��ϊ����悶�����ʂ�Ԃ�.
//!   \param x x �����̈ړ���.
//!   \param y y �����̈ړ���.
//!   \param z z �����̈ړ���.
//!   \param w w �ړ��ʂ̃X�P�[���t�@�N�^ (= 1.0f).
//!   \return ���s�ړ��������ʂ̕ϊ��s��.
Matrix translate(GLfloat x, GLfloat y, GLfloat z, GLfloat w = 1.0f) const
{
	Matrix m;
	return multiply(m.loadTranslate(x, y, z, w));
}

//! \brief ���s�ړ��ϊ����悶�����ʂ�Ԃ�.
//!   \param t �ړ��ʂ� GLfloat[4] �^�̔z�� (x, y, z, w).
//!   \return ���s�ړ��������ʂ̕ϊ��s��.
Matrix translate(const GLfloat *t) const
{
	return translate(t[0], t[1], t[2], t[3]);
}

//! \brief �g��k���ϊ����悶�����ʂ�Ԃ�.
//!   \param x x �����̊g�嗦.
//!   \param y y �����̊g�嗦.
//!   \param z z �����̊g�嗦.
//!   \param w w �ړ��ʂ̃X�P�[���t�@�N�^ (= 1.0f).
//!   \return �g��k���������ʂ̕ϊ��s��.
Matrix scale(GLfloat x, GLfloat y, GLfloat z, GLfloat w = 1.0f) const
{
	Matrix m;
	return multiply(m.loadScale(x, y, z, w));
}

//! \brief �g��k���ϊ����悶�����ʂ�Ԃ�.
//!   \param s �g�嗦�� GLfloat[4] �^�̔z�� (x, y, z, w).
//!   \return �g��k���������ʂ̕ϊ��s��.
Matrix scale(const GLfloat *s) const
{
	return scale(s[0], s[1], s[2], s[3]);
}

//! \brief x �����S�̉�]�ϊ����悶�����ʂ�Ԃ�.
//!   \param a ��]�p.
//!   \return x �����S�ɂ���� a ��]�����ϊ��s��.
Matrix rotateX(GLfloat a) const
{
	Matrix m;
	return multiply(m.loadRotateX(a));
}

//! \brief y �����S�̉�]�ϊ����悶�����ʂ�Ԃ�.
//!   \param a ��]�p.
//!   \return y �����S�ɂ���� a ��]�����ϊ��s��.
Matrix rotateY(GLfloat a) const
{
	Matrix m;
	return multiply(m.loadRotateY(a));
}

//! \brief z �����S�̉�]�ϊ����悶�����ʂ�Ԃ�.
//!   \param a ��]�p.
//!   \return z �����S�ɂ���� a ��]�����ϊ��s��.
Matrix rotateZ(GLfloat a) const
{
	Matrix m;
	return multiply(m.loadRotateZ(a));
}

//! \brief (x, y, z) �����̃x�N�g�������Ƃ����]�ϊ����悶�����ʂ�Ԃ�.
//!   \param x ��]���� x ����.
//!   \param y ��]���� y ����.
//!   \param z ��]���� z ����.
//!   \param a ��]�p.
//!   \return (x, y, z) �����ɂ���� a ��]�����ϊ��s��.
Matrix rotate(GLfloat x, GLfloat y, GLfloat z, GLfloat a) const
{
	Matrix m;
	return multiply(m.loadRotate(x, y, z, a));
}

//! \brief r �����̃x�N�g�������Ƃ����]�ϊ����悶�����ʂ�Ԃ�.
//!   \param r ��]���̕����x�N�g���Ɖ�]�p (x, y, z).
//!   \param a ��]�p.
//!   \return (r[0], r[1], r[2]) �����ɂ���� a ��]�����ϊ��s��.
Matrix rotate(const GLfloat *r, GLfloat a) const
{
	return rotate(r[0], r[1], r[2], a);
}

//! \brief r �����̃x�N�g�������Ƃ����]�̕ϊ��s����悶�����ʂ�Ԃ�.
//!   \param r ��]���̕����x�N�g���Ɖ�]�p (x, y, z, a).
//!   \return (r[0], r[1], r[2]) �����ɂ���� r[3] ��]�����ϊ��s��.
Matrix rotate(const GLfloat *r) const
{
	return rotate(r[0], r[1], r[2], r[3]);
}

//! \brief �r���[�ϊ����悶�����ʂ�Ԃ�.
//!   \param ex ���_�̈ʒu�� x ���W�l.
//!   \param ey ���_�̈ʒu�� y ���W�l.
//!   \param ez ���_�̈ʒu�� z ���W�l.
//!   \param tx �ڕW�_�̈ʒu�� x ���W�l.
//!   \param ty �ڕW�_�̈ʒu�� y ���W�l.
//!   \param tz �ڕW�_�̈ʒu�� z ���W�l.
//!   \param ux ������̃x�N�g���� x ����.
//!   \param uy ������̃x�N�g���� y ����.
//!   \param uz ������̃x�N�g���� z ����.
//!   \return �r���[�ϊ��s����悶���ϊ��s��.
Matrix lookat(GLfloat ex, GLfloat ey, GLfloat ez,
	GLfloat tx, GLfloat ty, GLfloat tz,
	GLfloat ux, GLfloat uy, GLfloat uz) const
{
	Matrix m;
	return multiply(m.loadLookat(ex, ey, ez, tx, ty, tz, ux, uy, uz));
}

//! \brief �r���[�ϊ����悶�����ʂ�Ԃ�.
//!   \param e ���_�̈ʒu�̔z��ϐ�.
//!   \param t �ڕW�_�̈ʒu�̔z��ϐ�.
//!   \param u ������̃x�N�g���̂̔z��ϐ�.
//!   \return �r���[�ϊ��s����悶���ϊ��s��.
Matrix lookat(const GLfloat *e, const GLfloat *t, const GLfloat *u) const
{
	return lookat(e[0], e[1], e[2], t[0], t[1], t[2], u[0], u[1], u[2]);
}

//! \brief ���𓊉e�ϊ����悶�����ʂ�Ԃ�.
//!   \param left �E�B���h�E�̍��[�̈ʒu.
//!   \param right �E�B���h�E�̉E�[�̈ʒu.
//!   \param bottom �E�B���h�E�̉��[�̈ʒu.
//!   \param top �E�B���h�E�̏�[�̈ʒu.
//!   \param zNear ���_����O���ʂ܂ł̈ʒu.
//!   \param zFar ���_�������ʂ܂ł̈ʒu.
//!   \return ���𓊉e�ϊ��s����悶���ϊ��s��.
Matrix orthogonal(GLfloat left, GLfloat right,
	GLfloat bottom, GLfloat top,
	GLfloat zNear, GLfloat zFar) const
{
	Matrix m;
	return multiply(m.loadOrthogonal(left, right, bottom, top, zNear, zFar));
}

//! \brief �������e�ϊ����悶�����ʂ�Ԃ�.
//!   \param left �E�B���h�E�̍��[�̈ʒu.
//!   \param right �E�B���h�E�̉E�[�̈ʒu.
//!   \param bottom �E�B���h�E�̉��[�̈ʒu.
//!   \param top �E�B���h�E�̏�[�̈ʒu.
//!   \param zNear ���_����O���ʂ܂ł̈ʒu.
//!   \param zFar ���_�������ʂ܂ł̈ʒu.
//!   \return �������e�ϊ��s����悶���ϊ��s��.
Matrix frustum(GLfloat left, GLfloat right,
	GLfloat bottom, GLfloat top,
	GLfloat zNear, GLfloat zFar) const
{
	Matrix m;
	return multiply(m.loadFrustum(left, right, bottom, top, zNear, zFar));
}

//! \brief ��p���w�肵�ē������e�ϊ����悶�����ʂ�Ԃ�.
//!   \param fovy y �����̉�p.
//!   \param aspect �c����.
//!   \param zNear ���_����O���ʂ܂ł̈ʒu.
//!   \param zFar ���_�������ʂ܂ł̈ʒu.
//!   \return �������e�ϊ��s����悶���ϊ��s��.
Matrix perspective(GLfloat fovy, GLfloat aspect,
	GLfloat zNear, GLfloat zFar) const
{
	Matrix m;
	return multiply(m.loadPerspective(fovy, aspect, zNear, zFar));
}

//! \brief �]�u�s���Ԃ�.
//!   \return �]�u�s��.
Matrix transpose() const
{
	Matrix t;
	return t.loadTranspose(*this);
}

//! \brief �t�s���Ԃ�.
//!   \return �t�s��.
Matrix invert() const
{
	Matrix t;
	return t.loadInvert(*this);
}

//! \brief �@���ϊ��s���Ԃ�.
//!   \return �@���ϊ��s��.
Matrix normal() const
{
	Matrix t;
	return t.loadNormal(*this);
}

//! \brief �x�N�g���ɑ΂��ē��e�ϊ����s��.
//!   \param c �ϊ����ʂ��i�[���� GLfloat[4] �^�̔z��.
//!   \param v ���̃x�N�g���� GLfloat[4] �^�̔z��.
void projection(GLfloat *c, const GLfloat *v) const
{
	projection(c, array, v);
}

//! \brief �ϊ��s������o��.
//!   \return �ϊ��s����i�[���� GLfloat[16] �^�̔z��.
const GLfloat *get() const
{
	return array;
}

//! \brief �ϊ��s������o��.
//!   \param a �ϊ��s����i�[���� GLfloat[16] �^�̔z��.
void get(GLfloat *a) const
{
	for (int i = 0; i < 16; ++i) a[i] = array[i];
}
};

//! \brief �P�ʍs���Ԃ�.
//!   \return �P�ʍs��
inline Matrix Identity()
{
	Matrix t;
	return t.loadIdentity();
};

//! \brief ���s�ړ��̕ϊ��s���Ԃ�.
//!   \param x x �����̈ړ���.
//!   \param y y �����̈ړ���.
//!   \param z z �����̈ړ���.
//!   \param w �ړ��ʂ̃X�P�[���t�@�N�^ (= 1.0f).
//!   \return ���s�ړ��̕ϊ��s��.
inline Matrix Translate(GLfloat x, GLfloat y, GLfloat z, GLfloat w = 1.0f)
{
	Matrix m;
	return m.loadTranslate(x, y, z, w);
}

//! \brief ���s�ړ��̕ϊ��s���Ԃ�.
//!   \param t �ړ��ʂ� GLfloat[4] �^�̔z�� (x, y, z, w).
//!   \return ���s�ړ��̕ϊ��s��
inline Matrix Translate(const GLfloat *t)
{
	Matrix m;
	return m.loadTranslate(t[0], t[1], t[2]);
}

//! \brief �g��k���̕ϊ��s���Ԃ�.
//!   \param x x �����̊g�嗦.
//!   \param y y �����̊g�嗦.
//!   \param z z �����̊g�嗦.
//!   \param w �g�嗦�̃X�P�[���t�@�N�^ (= 1.0f).
//!   \return �g��k���̕ϊ��s��.
inline Matrix Scale(GLfloat x, GLfloat y, GLfloat z, GLfloat w = 1.0f)
{
	Matrix m;
	return m.loadScale(x, y, z, w);
}

//! \brief �g��k���̕ϊ��s���Ԃ�.
//!   \param s �g�嗦�� GLfloat[4] �^�̔z�� (x, y, z, w).
//!   \return �g��k���̕ϊ��s��.
inline Matrix Scale(const GLfloat *s)
{
	Matrix m;
	return m.loadScale(s[0], s[1], s[2]);
}

//! \brief x �����S�̉�]�̕ϊ��s���Ԃ�.
//!   \param a ��]�p.
//!   \return x �����S�� a ������]����ϊ��s��.
inline Matrix RotateX(GLfloat a)
{
	Matrix m;
	return m.loadRotateX(a);
}

//! \brief y �����S�̉�]�̕ϊ��s���Ԃ�.
//!   \param a ��]�p.
//!   \return y �����S�� a ������]����ϊ��s��.
inline Matrix RotateY(GLfloat a)
{
	Matrix m;
	return m.loadRotateY(a);
}

//! \brief z �����S�̉�]�̕ϊ��s���Ԃ�.
//!   \param a ��]�p.
//!   \return z �����S�� a ������]����ϊ��s��.
inline Matrix RotateZ(GLfloat a)
{
	Matrix m;
	return m.loadRotateZ(a);
}

//! \brief (x, y, z) �����̃x�N�g�������Ƃ����]�̕ϊ��s����悶�����ʂ�Ԃ�.
//!   \param x ��]���� x ����.
//!   \param y ��]���� y ����.
//!   \param z ��]���� z ����.
//!   \param a ��]�p.
//!   \return (x, y, z) �����ɂ���� a ��]����ϊ��s��.
inline Matrix Rotate(GLfloat x, GLfloat y, GLfloat z, GLfloat a)
{
	Matrix m;
	return m.loadRotate(x, y, z, a);
}

//! \brief r �����̃x�N�g�������Ƃ����]�̕ϊ��s����悶�����ʂ�Ԃ�.
//!   \param r ��]���̃x�N�g����\�� GLfloat[3] �^�̔z��.
//!   \param a ��]�p.
//!   \return r ������ a ������]����ϊ��s��.
inline Matrix Rotate(const GLfloat *r, GLfloat a)
{
	Matrix m;
	return m.loadRotate(r[0], r[1], r[2], a);
}

//! \brief r �����̃x�N�g�������Ƃ����]�̕ϊ��s����悶�����ʂ�Ԃ�.
//!   \param r ��]���̃x�N�g���Ɖ�]�p��\�� GLfloat[4] �^�̔z��.
//!   \return (r[0], r[1], r[2]) ������ r[3] ������]����ϊ��s��.
inline Matrix Rotate(const GLfloat *r)
{
	Matrix m;
	return m.loadRotate(r[0], r[1], r[2], r[3]);
}

//! \brief �r���[�ϊ��s���Ԃ�.
//!   \param ex ���_�̈ʒu�� x ���W�l.
//!   \param ey ���_�̈ʒu�� y ���W�l.
//!   \param ez ���_�̈ʒu�� z ���W�l.
//!   \param tx �ڕW�_�̈ʒu�� x ���W�l.
//!   \param ty �ڕW�_�̈ʒu�� y ���W�l.
//!   \param tz �ڕW�_�̈ʒu�� z ���W�l.
//!   \param ux ������̃x�N�g���� x ����.
//!   \param uy ������̃x�N�g���� y ����.
//!   \param uz ������̃x�N�g���� z ����.
//!   \return ���߂��r���[�ϊ��s��.
inline Matrix Lookat(
	GLfloat ex, GLfloat ey, GLfloat ez,     // ���_�̈ʒu
	GLfloat tx, GLfloat ty, GLfloat tz,     // �ڕW�_�̈ʒu
	GLfloat ux, GLfloat uy, GLfloat uz      // ������̃x�N�g��
	)
{
	Matrix m;
	return m.loadLookat(ex, ey, ez, tx, ty, tz, ux, uy, uz);
}

//! \brief �r���[�ϊ��s���Ԃ�.
//!   \param e ���_�̈ʒu�̔z��ϐ�.
//!   \param t �ڕW�_�̈ʒu�̔z��ϐ�.
//!   \param u ������̃x�N�g���̂̔z��ϐ�.
//!   \return ���߂��r���[�ϊ��s��.
inline Matrix Lookat(
	const GLfloat *e,                       // ���_�̈ʒu
	const GLfloat *t,                       // �ڕW�_�̈ʒu
	const GLfloat *u                        // ������̃x�N�g��
	)
{
	Matrix m;
	return m.loadLookat(e[0], e[1], e[2], t[0], t[1], t[2], u[0], u[1], u[2]);
}

//! \brief ���𓊉e�ϊ��s���Ԃ�.
//!   \param left �E�B���h�E�̍��[�̈ʒu.
//!   \param right �E�B���h�E�̉E�[�̈ʒu.
//!   \param bottom �E�B���h�E�̉��[�̈ʒu.
//!   \param top �E�B���h�E�̏�[�̈ʒu.
//!   \param zNear ���_����O���ʂ܂ł̈ʒu.
//!   \param zFar ���_�������ʂ܂ł̈ʒu.
//!   \return ���߂����𓊉e�ϊ��s��.
inline Matrix Orthogonal(GLfloat left, GLfloat right,
	GLfloat bottom, GLfloat top,
	GLfloat zNear, GLfloat zFar)
{
	Matrix m;
	return m.loadOrthogonal(left, right, bottom, top, zNear, zFar);
}

//! \brief �����������e�ϊ��s���Ԃ�.
//!   \param left �E�B���h�E�̍��[�̈ʒu.
//!   \param right �E�B���h�E�̉E�[�̈ʒu.
//!   \param bottom �E�B���h�E�̉��[�̈ʒu.
//!   \param top �E�B���h�E�̏�[�̈ʒu.
//!   \param zNear ���_����O���ʂ܂ł̈ʒu.
//!   \param zFar ���_�������ʂ܂ł̈ʒu.
//!   \return ���߂��������e�ϊ��s��.
inline Matrix Frustum(GLfloat left, GLfloat right,
	GLfloat bottom, GLfloat top,
	GLfloat zNear, GLfloat zFar)
{
	Matrix m;
	return m.loadFrustum(left, right, bottom, top, zNear, zFar);
}

//! \brief ��p���w�肵�ē������e�ϊ��s���Ԃ�.
//!   \param fovy y �����̉�p.
//!   \param aspect �c����.
//!   \param zNear ���_����O���ʂ܂ł̈ʒu.
//!   \param zFar ���_�������ʂ܂ł̈ʒu.
//!   \return ���߂��������e�ϊ��s��.
inline Matrix Perspective(GLfloat fovy, GLfloat aspect,
	GLfloat zNear, GLfloat zFar)
{
	Matrix m;
	return m.loadPerspective(fovy, aspect, zNear, zFar);
}

//! \brief �]�u�s���Ԃ�.
//!   \param m ���̕ϊ��s��.
//!   \return m �̓]�u�s��.
inline Matrix Transpose(const Matrix &m)
{
	return m.transpose();
}

//! \brief �t�s���Ԃ�.
//!   \param m ���̕ϊ��s��.
//!   \return m �̋t�s��.
inline Matrix Invert(const Matrix &m)
{
	return m.invert();
}

//! \brief �@���ϊ��s���Ԃ�.
//!   \param m ���̕ϊ��s��.
//!   \return m �̖@���ϊ��s��.
inline Matrix Normal(const Matrix &m)
{
	return m.normal();
}