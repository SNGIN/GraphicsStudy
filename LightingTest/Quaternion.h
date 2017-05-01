#pragma once
#include "Commonheader.h"

class Quaternion
{


	// �l���� p �Ǝl���� q �̘a���l���� r �ɋ��߂�
	void add(GLfloat *r, const GLfloat *p, const GLfloat *q) const{
		r[0] = p[0] + q[0];
		r[1] = p[1] + q[1];
		r[2] = p[2] + q[2];
		r[3] = p[3] + q[3];
	}

	// �l���� p �Ǝl���� q �̍����l���� r �ɋ��߂�
	void subtract(GLfloat *r, const GLfloat *p, const GLfloat *q) const{
		r[0] = p[0] - q[0];
		r[1] = p[1] - q[1];
		r[2] = p[2] - q[2];
		r[3] = p[3] - q[3];
	}

	// �l���� p �Ǝl���� q �̐ς��l���� r �ɋ��߂�
	void multiply(GLfloat *r, const GLfloat *p, const GLfloat *q) const{
		r[0] = p[1] * q[2] - p[2] * q[1] + p[0] * q[3] + p[3] * q[0];
		r[1] = p[2] * q[0] - p[0] * q[2] + p[1] * q[3] + p[3] * q[1];
		r[2] = p[0] * q[1] - p[1] * q[0] + p[2] * q[3] + p[3] * q[2];
		r[3] = p[3] * q[3] - p[0] * q[0] - p[1] * q[1] - p[2] * q[2];
	}

	// �l���� q ���\����]�̕ϊ��s��� m �ɋ��߂�
	void toMatrix(GLfloat *m, const GLfloat *q) const{
		GLfloat xx = q[0] * q[0] * 2.0f;
		GLfloat yy = q[1] * q[1] * 2.0f;
		GLfloat zz = q[2] * q[2] * 2.0f;
		GLfloat xy = q[0] * q[1] * 2.0f;
		GLfloat yz = q[1] * q[2] * 2.0f;
		GLfloat zx = q[2] * q[0] * 2.0f;
		GLfloat xw = q[0] * q[3] * 2.0f;
		GLfloat yw = q[1] * q[3] * 2.0f;
		GLfloat zw = q[2] * q[3] * 2.0f;

		m[0] = 1.0f - yy - zz;
		m[1] = xy + zw;
		m[2] = zx - yw;
		m[4] = xy - zw;
		m[5] = 1.0f - zz - xx;
		m[6] = yz + xw;
		m[8] = zx + yw;
		m[9] = yz - xw;
		m[10] = 1.0f - xx - yy;
		m[3] = m[7] = m[11] = m[12] = m[13] = m[14] = 0.0f;
		m[15] = 1.0f;
	}

	// ��]�̕ϊ��s�� m ���\���l������ q �ɋ��߂�
	void toQuaternion(GLfloat *q, const GLfloat *m) const{
		GLfloat tr = m[0] + m[5] + m[10] + m[15];

		if (tr > 0.0f)
		{
			q[3] = sqrt(tr) * 0.5f;
			q[0] = (m[6] - m[9]) * 0.25f / q[3];
			q[1] = (m[8] - m[2]) * 0.25f / q[3];
			q[2] = (m[1] - m[4]) * 0.25f / q[3];
		}
	}

	// ���ʐ��`��� q �� r �� t �ŕ�Ԃ����l������ p �ɋ��߂�
	void slerp(GLfloat *p, const GLfloat *q, const GLfloat *r, GLfloat t) const{
		GLfloat qr = q[0] * r[0] + q[1] * r[1] + q[2] * r[2] + q[3] * r[3];
		GLfloat ss = 1.0f - qr * qr;

		if (ss == 0.0f)
		{
			if (p != q)
			{
				p[0] = q[0];
				p[1] = q[1];
				p[2] = q[2];
				p[3] = q[3];
			}
		}
		else
		{
			GLfloat sp = sqrt(ss);
			GLfloat ph = acos(qr);
			GLfloat pt = ph * t;
			GLfloat t1 = sin(pt) / sp;
			GLfloat t0 = sin(ph - pt) / sp;

			p[0] = q[0] * t0 + r[0] * t1;
			p[1] = q[1] * t0 + r[1] * t1;
			p[2] = q[2] * t0 + r[2] * t1;
			p[3] = q[3] * t0 + r[3] * t1;
		}
	}

public:

	// �l�����̗v�f
	GLfloat array[4];

	// �f�X�g���N�^
	virtual ~Quaternion(void) {}

	// �R���X�g���N�^
	Quaternion(void) {}
	Quaternion(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
	{
		load(x, y, z, w);
	}
	Quaternion(const GLfloat *a)
	{
		load(a);
	}
	Quaternion(const Quaternion &q)
	{
		load(q);
	}

	// �l������ݒ肷��
	Quaternion &load(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
	{
		array[0] = x;
		array[1] = y;
		array[2] = z;
		array[3] = w;
		return *this;
	}
	Quaternion &load(const GLfloat *a)
	{
		return load(a[0], a[1], a[2], a[3]);
	}
	Quaternion &load(const Quaternion &q)
	{
		return load(q.array);
	}

	// �l�����̘a�����߂�
	Quaternion &loadAdd(const GLfloat *a, const GLfloat *b)
	{
		add(array, a, b);
		return *this;
	}
	Quaternion &loadAdd(const Quaternion &q, const Quaternion &r)
	{
		return loadAdd(q.array, r.array);
	}
	Quaternion &loadAdd(const GLfloat *a, const Quaternion &q)
	{
		return loadAdd(a, q.array);
	}
	Quaternion &loadAdd(const Quaternion &q, const GLfloat *a)
	{
		return loadAdd(q.array, a);
	}
	Quaternion &loadAdd(const GLfloat *a)
	{
		return loadAdd(array, a);
	}
	Quaternion &loadAdd(const Quaternion &q)
	{
		return loadAdd(q.array);
	}
	Quaternion add(const GLfloat *a) const
	{
		Quaternion t;
		add(t.array, array, a);
		return t;
	}
	Quaternion add(const Quaternion &q) const
	{
		return add(q.array);
	}

	// �l�����̍������߂�
	Quaternion &loadSubtract(const GLfloat *a, const GLfloat *b)
	{
		subtract(array, a, b);
		return *this;
	}
	Quaternion &loadSubtract(const Quaternion &q, const Quaternion &r)
	{
		return loadSubtract(q.array, r.array);
	}
	Quaternion &loadSubtract(const GLfloat *a, const Quaternion &q)
	{
		return loadSubtract(a, q.array);
	}
	Quaternion &loadSubtract(const Quaternion &q, const GLfloat *a)
	{
		return loadSubtract(q.array, a);
	}
	Quaternion &loadSubtract(const GLfloat *a)
	{
		return loadSubtract(array, a);
	}
	Quaternion &loadSubtract(const Quaternion &q)
	{
		return loadSubtract(q.array);
	}
	Quaternion subtract(const GLfloat *a) const
	{
		Quaternion t;
		subtract(t.array, array, a);
		return t;
	}
	Quaternion subtract(const Quaternion &q) const
	{
		return subtract(q.array);
	}

	// �l�����̐ς����߂�
	Quaternion &loadMultiply(const GLfloat *a, const GLfloat *b)
	{
		multiply(array, a, b);
		return *this;
	}
	Quaternion &loadMultiply(const Quaternion &q, const Quaternion &r)
	{
		return loadMultiply(q.array, r.array);
	}
	Quaternion &loadMultiply(const GLfloat *a, const Quaternion &q)
	{
		return loadMultiply(a, q.array);
	}
	Quaternion &loadMultiply(const Quaternion &q, const GLfloat *a)
	{
		return loadMultiply(q.array, a);
	}
	Quaternion &loadMultiply(const GLfloat *a)
	{
		Quaternion t = *this;
		return loadMultiply(t.array, a);
	}
	Quaternion &loadMultiply(const Quaternion &q)
	{
		return loadMultiply(q.array);
	}
	Quaternion multiply(const GLfloat *a) const
	{
		Quaternion t;
		multiply(t.array, array, a);
		return t;
	}
	Quaternion multiply(const Quaternion &q) const
	{
		return multiply(q.array);
	}

	// ���Z�q
	Quaternion &operator=(const GLfloat *a)
	{
		return load(a);
	}
	Quaternion &operator=(const Quaternion &q)
	{
		return load(q);
	}
	Quaternion operator+(const GLfloat *a) const
	{
		return add(a);
	}
	Quaternion operator+(const Quaternion &q) const
	{
		return add(q);
	}
	Quaternion &operator+=(const GLfloat *a)
	{
		return loadAdd(a);
	}
	Quaternion &operator+=(const Quaternion &q)
	{
		return loadAdd(q);
	}
	Quaternion operator-(const GLfloat *a) const
	{
		return subtract(a);
	}
	Quaternion operator-(const Quaternion &q) const
	{
		return subtract(q);
	}
	Quaternion &operator-=(const GLfloat *a)
	{
		return loadSubtract(a);
	}
	Quaternion &operator-=(const Quaternion &q)
	{
		return loadSubtract(q);
	}
	Quaternion operator*(const GLfloat *a) const
	{
		return multiply(a);
	}
	Quaternion operator*(const Quaternion &q) const
	{
		return multiply(q);
	}
	Quaternion &operator*=(const GLfloat *a)
	{
		return loadMultiply(a);
	}
	Quaternion &operator*=(const Quaternion &q)
	{
		return loadMultiply(q);
	}

	// ��]�̕ϊ��s�� m ��\���l������ݒ肷��
	Quaternion &loadMatrix(const GLfloat *m)
	{
		toQuaternion(array, m);
		return *this;
	}

	// �P�ʌ���ݒ肷��
	Quaternion &loadIdentity(void)
	{
		return load(0.0f, 0.0f, 0.0f, 1.0f);
	}

	// (x, y, z) �����Ƃ��Ċp�x a ��]����l������ݒ肷��
	Quaternion &loadRotate(GLfloat x, GLfloat y, GLfloat z, GLfloat a){
		GLfloat l = x * x + y * y + z * z;

		if (l != 0.0)
		{
			GLfloat s = sin(a *= 0.5f) / sqrt(l);

			array[0] = x * s;
			array[1] = y * s;
			array[2] = z * s;
		}
		else
		{
			array[0] = array[1] = array[2] = 0.0f;
		}
		array[3] = cos(a);

		return *this;
	}
	Quaternion &loadRotate(const GLfloat *v, GLfloat a)
	{
		return loadRotate(v[0], v[1], v[2], a);
	}

	// �l������ (x, y, z) �����Ƃ��Ċp�x a ��]����
	Quaternion rotate(GLfloat x, GLfloat y, GLfloat z, GLfloat a) const
	{
		Quaternion q;
		return multiply(q.loadRotate(x, y, z, a));
	}
	Quaternion rotate(const GLfloat *v, GLfloat a) const
	{
		return multiply(rotate(v[0], v[1], v[2], a));
	}
	Quaternion rotate(const GLfloat *v) const
	{
		return multiply(rotate(v[0], v[1], v[2], v[3]));
	}

	// �I�C���[�p (h, p, r) �ŗ^����ꂽ��]��\���l������ݒ肷��
	Quaternion &loadEuler(GLfloat h, GLfloat p, GLfloat r);
	Quaternion &loadEuler(const GLfloat *e)
	{
		return loadEuler(e[0], e[1], e[2]);
	}

	// �l�������I�C���[�p (h, p, r) �ŉ�]����
	Quaternion euler(GLfloat h, GLfloat p, GLfloat r) const
	{
		Quaternion q;
		return multiply(q.loadEuler(h, p, r));
	}
	Quaternion euler(const GLfloat *e) const
	{
		return multiply(euler(e[0], e[1], e[2]));
	}

	// ���ʐ��`���
	Quaternion &loadSlerp(const GLfloat *a, const GLfloat *b, GLfloat t)
	{
		slerp(array, a, b, t);
		return *this;
	}
	Quaternion &loadSlerp(const Quaternion &q, const Quaternion &r, GLfloat t)
	{
		return loadSlerp(q.array, r.array, t);
	}
	Quaternion &loadSlerp(const Quaternion &q, const GLfloat *a, GLfloat t)
	{
		return loadSlerp(q.array, a, t);
	}
	Quaternion &loadSlerp(const GLfloat *a, const Quaternion &q, GLfloat t)
	{
		return loadSlerp(a, q.array, t);
	}
	Quaternion slerp(GLfloat *a, GLfloat t) const
	{
		Quaternion q;
		slerp(q.array, array, a, t);
		return q;
	}
	Quaternion slerp(const Quaternion &q, GLfloat t) const
	{
		return slerp(q.array, t);
	}

	// �l�����̃m���������߂�
	GLfloat norm(void) const{
		return sqrt(array[0] * array[0] + array[1] * array[1] + array[2] * array[2] + array[3] * array[3]);
	}

	// �����l���������߂�
	Quaternion conjugate(void) const{
		Quaternion t(-array[0], -array[1], -array[2], array[3]);

		return t;
	}

	// �l�����̋t�����߂�
	Quaternion invert(void) const{
		Quaternion t = conjugate();
		GLfloat l = array[0] * array[0] + array[1] * array[1] + array[2] * array[2] + array[3] * array[3];

		if (l > 0.0f)
		{
			t.array[0] /= l;
			t.array[1] /= l;
			t.array[2] /= l;
			t.array[3] /= l;
		}

		return t;
	}

	// �l�����𐳋K������
	Quaternion normalize(void) const{
		Quaternion t = *this;
		GLfloat l = norm();

		if (l > 0.0f)
		{
			t.array[0] /= l;
			t.array[1] /= l;
			t.array[2] /= l;
			t.array[3] /= l;
		}

		return t;
	}

	// �l���������o��
	const GLfloat *get(void) const
	{
		return array;
	}
	void get(GLfloat *a) const
	{
		a[0] = array[0];
		a[1] = array[1];
		a[2] = array[2];
		a[3] = array[3];
	}

	// �l�������\����]�̍s��� m �ɋ��߂�
	void getMatrix(GLfloat *m) const
	{
		toMatrix(m, array);
	}
};

// (x, y, z) �����Ƃ��Ċp�x a ��]����l���������߂�
inline Quaternion RotateQuaternion(GLfloat x, GLfloat y, GLfloat z, GLfloat a)
{
	Quaternion t;
	t.loadRotate(x, y, z, a);
	return t;
}