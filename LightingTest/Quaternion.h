#pragma once
#include "Commonheader.h"

class Quaternion
{


	// 四元数 p と四元数 q の和を四元数 r に求める
	void add(GLfloat *r, const GLfloat *p, const GLfloat *q) const{
		r[0] = p[0] + q[0];
		r[1] = p[1] + q[1];
		r[2] = p[2] + q[2];
		r[3] = p[3] + q[3];
	}

	// 四元数 p と四元数 q の差を四元数 r に求める
	void subtract(GLfloat *r, const GLfloat *p, const GLfloat *q) const{
		r[0] = p[0] - q[0];
		r[1] = p[1] - q[1];
		r[2] = p[2] - q[2];
		r[3] = p[3] - q[3];
	}

	// 四元数 p と四元数 q の積を四元数 r に求める
	void multiply(GLfloat *r, const GLfloat *p, const GLfloat *q) const{
		r[0] = p[1] * q[2] - p[2] * q[1] + p[0] * q[3] + p[3] * q[0];
		r[1] = p[2] * q[0] - p[0] * q[2] + p[1] * q[3] + p[3] * q[1];
		r[2] = p[0] * q[1] - p[1] * q[0] + p[2] * q[3] + p[3] * q[2];
		r[3] = p[3] * q[3] - p[0] * q[0] - p[1] * q[1] - p[2] * q[2];
	}

	// 四元数 q が表す回転の変換行列を m に求める
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

	// 回転の変換行列 m が表す四元数を q に求める
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

	// 球面線形補間 q と r を t で補間した四元数を p に求める
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

	// 四元数の要素
	GLfloat array[4];

	// デストラクタ
	virtual ~Quaternion(void) {}

	// コンストラクタ
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

	// 四元数を設定する
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

	// 四元数の和を求める
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

	// 四元数の差を求める
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

	// 四元数の積を求める
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

	// 演算子
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

	// 回転の変換行列 m を表す四元数を設定する
	Quaternion &loadMatrix(const GLfloat *m)
	{
		toQuaternion(array, m);
		return *this;
	}

	// 単位元を設定する
	Quaternion &loadIdentity(void)
	{
		return load(0.0f, 0.0f, 0.0f, 1.0f);
	}

	// (x, y, z) を軸として角度 a 回転する四元数を設定する
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

	// 四元数を (x, y, z) を軸として角度 a 回転する
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

	// オイラー角 (h, p, r) で与えられた回転を表す四元数を設定する
	Quaternion &loadEuler(GLfloat h, GLfloat p, GLfloat r);
	Quaternion &loadEuler(const GLfloat *e)
	{
		return loadEuler(e[0], e[1], e[2]);
	}

	// 四元数をオイラー角 (h, p, r) で回転する
	Quaternion euler(GLfloat h, GLfloat p, GLfloat r) const
	{
		Quaternion q;
		return multiply(q.loadEuler(h, p, r));
	}
	Quaternion euler(const GLfloat *e) const
	{
		return multiply(euler(e[0], e[1], e[2]));
	}

	// 球面線形補間
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

	// 四元数のノルムを求める
	GLfloat norm(void) const{
		return sqrt(array[0] * array[0] + array[1] * array[1] + array[2] * array[2] + array[3] * array[3]);
	}

	// 共役四元数を求める
	Quaternion conjugate(void) const{
		Quaternion t(-array[0], -array[1], -array[2], array[3]);

		return t;
	}

	// 四元数の逆を求める
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

	// 四元数を正規化する
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

	// 四元数を取り出す
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

	// 四元数が表す回転の行列を m に求める
	void getMatrix(GLfloat *m) const
	{
		toMatrix(m, array);
	}
};

// (x, y, z) を軸として角度 a 回転する四元数を求める
inline Quaternion RotateQuaternion(GLfloat x, GLfloat y, GLfloat z, GLfloat a)
{
	Quaternion t;
	t.loadRotate(x, y, z, a);
	return t;
}