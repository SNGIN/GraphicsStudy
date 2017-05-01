#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "opengl32.lib")

#pragma once

#include "glew.h"
#include "glfw3.h"
#include <math.h>

class Matrix
{
	// 変換行列の要素
	GLfloat array[16];

	// 行列 a とベクトル b の積をベクトル c に代入する
	void projection(GLfloat *c, const GLfloat *a, const GLfloat *b) const{
		for (int i = 0; i < 4; ++i)
		{
			c[i] = a[0 + i] * b[0] + a[4 + i] * b[1] + a[8 + i] * b[2] + a[12 + i] * b[3];
		}
	}

	// 行列 a と行列 b の積を行列 c に代入する
	void multiply(GLfloat *c, const GLfloat *a, const GLfloat *b) const{
		for (int i = 0; i < 16; ++i)
		{
			int j = i & 3, k = i & ~3;

			c[i] = a[0 + j] * b[k + 0] + a[4 + j] * b[k + 1] + a[8 + j] * b[k + 2] + a[12 + j] * b[k + 3];
		}
	}

public:

	//! \brief デストラクタ.
	virtual ~Matrix() {}

	//! \brief コンストラクタ.
	Matrix() {}

	//! \brief コンストラクタ.
	//!   \param a GLfloat[16] 型の配列.
	Matrix(const GLfloat *a)
	{
		load(a);
	}

	//! \brief コピーコンストラクタ.
	//!   \param m Matrix 型の変数.
	Matrix(const Matrix &m)
	{
		load(m);
	}

	//! \brief 配列変数の値を格納する.
	//!   \param a GLfloat[16] 型の配列.
	//!   \return a を代入した Matrix 型の値.
	Matrix &load(const GLfloat *a)
	{
		for (int i = 0; i < 16; ++i) array[i] = a[i];
		return *this;
	}

	//! \brief 別の変換行列の値を格納する.
	//!   \param m Matrix 型の変数.
	//!   \return m を代入した Matrix 型の値.
	Matrix &load(const Matrix &m)
	{
		return load(m.array);
	}

	//! \brief 変換行列に配列に格納した変換行列を加算した結果を格納する.
	//!   \param a GLfloat[16] 型の配列.
	//!   \return 変換行列に a を加えた Matrix 型の値.
	Matrix &loadAdd(const GLfloat *a)
	{
		for (int i = 0; i < 16; ++i) array[i] += a[i];
		return *this;
	}

	//! \brief 変換行列に別の変換行列を加算した結果を格納する.
	//!   \param m Matrix 型の変数.
	//!   \return 変換行列に m を加えた Matrix 型の値.
	Matrix &loadAdd(const Matrix &m)
	{
		return loadAdd(m.array);
	}

	//! \brief 変換行列から配列に格納した変換行列を減算した結果を格納する.
	//!   \param a GLfloat[16] 型の配列.
	//!   \return 変換行列に a を引いた Matrix 型の値.
	Matrix &loadSubtract(const GLfloat *a)
	{
		for (int i = 0; i < 16; ++i) array[i] -= a[i];
		return *this;
	}

	//! \brief 変換行列から別の変換行列を減算した結果を格納する.
	//!   \param m Matrix 型の変数.
	//!   \return 変換行列に m を引いた Matrix 型の値.
	Matrix &loadSubtract(const Matrix &m)
	{
		return loadSubtract(m.array);
	}

	//! \brief 変換行列に配列に格納した変換行列を乗算した結果を格納する.
	//!   \param a GLfloat[16] 型の配列.
	//!   \return 変換行列に a を掛けた Matrix 型の値.
	Matrix &loadMultiply(const GLfloat *a)
	{
		return load(multiply(a));
	}

	//! \brief 変換行列に別の変換行列を乗算した結果を格納する.
	//!   \param m Matrix 型の変数.
	//!   \return 変換行列に m を掛けた Matrix 型の値.
	Matrix &loadMultiply(const Matrix &m)
	{
		return loadMultiply(m.array);
	}

	//! \brief 変換行列を配列に格納した変換行列で除算した結果を格納する.
	//!   \param a GLfloat[16] 型の配列.
	//!   \return 変換行列に a を乗じた Matrix 型の値.
	Matrix &loadDivide(const GLfloat *a)
	{
		return load(divide(a));
	}

	//! \brief 変換行列を別の変換行列で除算した結果を格納する.
	//!   \param m Matrix 型の変数.
	//!   \return 変換行列に m を乗じた Matrix 型の値.
	Matrix &loadDivide(const Matrix &m)
	{
		return loadDivide(m.array);
	}

	//! \brief 変換行列に配列に格納した変換行列を加算した値を返す.
	//!   \param a GLfloat[16] 型の配列.
	//!   \return 変換行列に a を加えた Matrix 型の値.
	Matrix add(const GLfloat *a) const
	{
		Matrix t;
		return t.loadAdd(a);
	}

	//! \brief 変換行列に別の変換行列を加算した値を返す.
	//!   \param m Matrix 型の変数.
	//!   \return 変換行列に m を加えた Matrix 型の値.
	Matrix add(const Matrix &m) const
	{
		return add(m.array);
	}

	//! \brief 変換行列から配列に格納した変換行列を減算した値を返す.
	//!   \param a GLfloat[16] 型の配列.
	//!   \return 変換行列に a を引いた Matrix 型の値.
	Matrix subtract(const GLfloat *a) const
	{
		Matrix t;
		return t.loadSubtract(a);
	}

	//! \brief 変換行列から別の変換行列を減算した値を返す.
	//!   \param m Matrix 型の変数.
	//!   \return 変換行列に m を引いた Matrix 型の値.
	Matrix subtract(const Matrix &m) const
	{
		return subtract(m.array);
	}

	//! \brief 変換行列に配列に格納した変換行列を乗算した値を返す.
	//!   \param a GLfloat[16] 型の配列.
	//!   \return 変換行列に a を掛けた Matrix 型の値.
	Matrix multiply(const GLfloat *a) const
	{
		Matrix t;
		multiply(t.array, array, a);
		return t;
	}
//!   \param m Matrix 型の変数.
//!   \return 変換行列に m を掛けた Matrix 型の値.
Matrix multiply(const Matrix &m) const
{
	return multiply(m.array);
}

//! \brief 変換行列を配列に格納した変換行列で除算した値を返す.
//!   \param a GLfloat[16] 型の配列.
//!   \return 変換行列を a で割った Matrix 型の値.
Matrix divide(const GLfloat *a) const
{
	Matrix t, ia;
	ia.loadInvert(a);
	multiply(t.array, array, ia.array);
	return t;
}

//! \brief 変換行列を配列に格納した変換行列で除算した値を返す.
//!   \param m Matrix 型の変数.
//!   \return 変換行列を m で割った Matrix 型の値.
Matrix divide(const Matrix &m) const
{
	return divide(m.array);
}

// 演算子
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

//! \brief 単位行列を格納する.
Matrix &loadIdentity();

//! \brief 平行移動の変換行列を格納する.
//!   \param x x 方向の移動量.
//!   \param y y 方向の移動量.
//!   \param z z 方向の移動量.
//!   \param w w 移動量のスケールファクタ (= 1.0f).
//!   \return 設定した変換行列.
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

//! \brief 平行移動の変換行列を格納する.
//!   \param t 移動量の GLfloat[4] 型の配列 (x, y, z, w).
//!   \return 設定した変換行列.
Matrix &loadTranslate(const GLfloat *t)
{
	return loadTranslate(t[0], t[1], t[2], t[3]);
}

//! \brief 拡大縮小の変換行列を格納する.
//!   \param x x 方向の拡大率.
//!   \param y y 方向の拡大率.
//!   \param z z 方向の拡大率.
//!   \param w w 拡大率のスケールファクタ (= 1.0f).
//!   \return 設定した変換行列.
Matrix &loadScale(GLfloat x, GLfloat y, GLfloat z, GLfloat w = 1.0f);

//! \brief 拡大縮小の変換行列を格納する.
//!   \param s 拡大率の GLfloat[4] 型の配列 (x, y, z, w).
//!   \return 設定した変換行列.
Matrix &loadScale(const GLfloat *s)
{
	return loadScale(s[0], s[1], s[2], s[3]);
}

//! \brief x 軸中心の回転の変換行列を格納する.
//!   \param a 回転角.
//!   \return 設定した変換行列.
Matrix &loadRotateX(GLfloat a){
	GLfloat c = cos(a);
	GLfloat s = sin(a);

	array[0] = 1.0f; array[1] = 0.0f; array[2] = 0.0f; array[3] = 0.0f;
	array[4] = 0.0f; array[5] = c;    array[6] = s;    array[7] = 0.0f;
	array[8] = 0.0f; array[9] = -s;   array[10] = c;    array[11] = 0.0f;
	array[12] = 0.0f; array[13] = 0.0f; array[14] = 0.0f; array[15] = 1.0f;

	return *this;
}

//! \brief y 軸中心の回転の変換行列を格納する.
//!   \param a 回転角.
//!   \return 設定した変換行列.
Matrix &loadRotateY(GLfloat a);

//! \brief z 軸中心の回転の変換行列を格納する.
//!   \param a 回転角.
//!   \return 設定した変換行列.
Matrix &loadRotateZ(GLfloat a);

//! \brief (x, y, z) 方向のベクトルを軸とする回転の変換行列を格納する.
//!   \param x 回転軸の x 成分.
//!   \param y 回転軸の y 成分.
//!   \param z 回転軸の z 成分.
//!   \param a 回転角.
//!   \return 設定した変換行列.
Matrix &loadRotate(GLfloat x, GLfloat y, GLfloat z, GLfloat a);

//! \brief r 方向のベクトルを軸とする回転の変換行列を格納する.
//!   \param r 回転軸の方向ベクトル (x, y, z).
//!   \param a 回転角.
//!   \return 設定した変換行列.
Matrix &loadRotate(const GLfloat *r, GLfloat a)
{
	return loadRotate(r[0], r[1], r[2], a);
}

//! \brief r 方向のベクトルを軸とする回転の変換行列を格納する.
//!   \param r 回転軸の方向ベクトルと回転角 (x, y, z, a).
//!   \return 設定した変換行列.
Matrix &loadRotate(const GLfloat *r)
{
	return loadRotate(r[0], r[1], r[2], r[3]);
}

//! \brief ビュー変換行列を格納する.
//!   \param ex 視点の位置の x 座標値.
//!   \param ey 視点の位置の y 座標値.
//!   \param ez 視点の位置の z 座標値.
//!   \param tx 目標点の位置の x 座標値.
//!   \param ty 目標点の位置の y 座標値.
//!   \param tz 目標点の位置の z 座標値.
//!   \param ux 上方向のベクトルの x 成分.
//!   \param uy 上方向のベクトルの y 成分.
//!   \param uz 上方向のベクトルの z 成分.
//!   \return 設定したビュー変換行列.
Matrix &loadLookat(GLfloat ex, GLfloat ey, GLfloat ez,
	GLfloat tx, GLfloat ty, GLfloat tz,
	GLfloat ux, GLfloat uy, GLfloat uz){
	// z 軸 = e - t
	GLfloat zx = ex - tx;
	GLfloat zy = ey - ty;
	GLfloat zz = ez - tz;
	const GLfloat zl = sqrt(zx * zx + zy * zy + zz * zz);
	if (zl == 0.0f) return *this;

	// z 軸の正規化
	zx /= zl;
	zy /= zl;
	zz /= zl;

	// x 軸 = u x z 軸
	GLfloat xx = uy * zz - uz * zy;
	GLfloat xy = uz * zx - ux * zz;
	GLfloat xz = ux * zy - uy * zx;
	const GLfloat xl = sqrt(xx * xx + xy * xy + xz * xz);
	if (xl == 0.0f) return *this;

	// x 軸の正規化
	xx /= xl;
	xy /= xl;
	xz /= xl;

	// z 軸
	array[2] = zx;
	array[6] = zy;
	array[10] = zz;

	// x 軸
	array[0] = xx;
	array[4] = xy;
	array[8] = xz;

	// y 軸 = z 軸 x x 軸
	array[1] = zy * xz - zz * xy;
	array[5] = zz * xx - zx * xz;
	array[9] = zx * xy - zy * xx;

	// 平行移動
	array[12] = -(ex * array[0] + ey * array[4] + ez * array[8]);
	array[13] = -(ex * array[1] + ey * array[5] + ez * array[9]);
	array[14] = -(ex * array[2] + ey * array[6] + ez * array[10]);

	// 残り
	array[3] = array[7] = array[11] = 0.0f;
	array[15] = 1.0f;

	return *this;
}

//! \brief ビュー変換行列を格納する.
//!   \param e 視点の位置の配列変数.
//!   \param t 目標点の位置の配列変数.
//!   \param u 上方向のベクトルのの配列変数.
//!   \return 設定したビュー変換行列.
Matrix &loadLookat(const GLfloat *e, const GLfloat *t, const GLfloat *u)
{
	return loadLookat(e[0], e[1], e[2], t[0], t[1], t[2], u[0], u[1], u[2]);
}

//! \brief 直交投影変換行列を格納する.
//!   \param left ウィンドウの左端の位置.
//!   \param right ウィンドウの右端の位置.
//!   \param bottom ウィンドウの下端の位置.
//!   \param top ウィンドウの上端の位置.
//!   \param zNear 視点から前方面までの位置.
//!   \param zFar 視点から後方面までの位置.
//!   \return 設定した直交投影変換行列.
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

//! \brief 透視透視投影変換行列を格納する.
//!   \param left ウィンドウの左端の位置.
//!   \param right ウィンドウの右端の位置.
//!   \param bottom ウィンドウの下端の位置.
//!   \param top ウィンドウの上端の位置.
//!   \param zNear 視点から前方面までの位置.
//!   \param zFar 視点から後方面までの位置.
//!   \return 設定した透視投影変換行列.
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

//! \brief 画角を指定して透視投影変換行列を格納する.
//!   \param fovy y 方向の画角.
//!   \param aspect 縦横比.
//!   \param zNear 視点から前方面までの位置.
//!   \param zFar 視点から後方面までの位置.
//!   \return 設定した透視投影変換行列.
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

//! \brief 転置行列を格納する.
//!   \param a GLfloat[16] 型の変換行列.
//!   \return 設定した a の転置行列.
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

//! \brief 転置行列を格納する.
//!   \param m Matrix 型の変換行列.
//!   \return 設定した m の転置行列.
Matrix &loadTranspose(const Matrix &m)
{
	return loadTranspose(m.array);
}

//! \brief 逆行列を格納する.
//!   \param a GLfloat[16] 型の変換行列.
//!   \return 設定した a の逆行列.
Matrix &loadInvert(const GLfloat *a);

//! \brief 逆行列を格納する.
//!   \param m Matrix 型の変換行列.
//!   \return 設定した m の逆行列.
Matrix &loadInvert(const Matrix &m)
{
	return loadInvert(m.array);
}

//! \brief 法線変換行列を格納する.
//!   \param a GLfloat[16] 型の変換行列.
//!   \return 設定した m の法線変換行列.
Matrix &loadNormal(const GLfloat *marray){
	//変換行列：法線変換行列を設定する

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

//! \brief 法線変換行列を格納する.
//!   \param Matrix 型の変換行列.
//!   \return 設定した m の法線変換行列.
Matrix &loadNormal(const Matrix &m)
{
	return loadNormal(m.array);
}

//! \brief 平行移動変換を乗じた結果を返す.
//!   \param x x 方向の移動量.
//!   \param y y 方向の移動量.
//!   \param z z 方向の移動量.
//!   \param w w 移動量のスケールファクタ (= 1.0f).
//!   \return 平行移動した結果の変換行列.
Matrix translate(GLfloat x, GLfloat y, GLfloat z, GLfloat w = 1.0f) const
{
	Matrix m;
	return multiply(m.loadTranslate(x, y, z, w));
}

//! \brief 平行移動変換を乗じた結果を返す.
//!   \param t 移動量の GLfloat[4] 型の配列 (x, y, z, w).
//!   \return 平行移動した結果の変換行列.
Matrix translate(const GLfloat *t) const
{
	return translate(t[0], t[1], t[2], t[3]);
}

//! \brief 拡大縮小変換を乗じた結果を返す.
//!   \param x x 方向の拡大率.
//!   \param y y 方向の拡大率.
//!   \param z z 方向の拡大率.
//!   \param w w 移動量のスケールファクタ (= 1.0f).
//!   \return 拡大縮小した結果の変換行列.
Matrix scale(GLfloat x, GLfloat y, GLfloat z, GLfloat w = 1.0f) const
{
	Matrix m;
	return multiply(m.loadScale(x, y, z, w));
}

//! \brief 拡大縮小変換を乗じた結果を返す.
//!   \param s 拡大率の GLfloat[4] 型の配列 (x, y, z, w).
//!   \return 拡大縮小した結果の変換行列.
Matrix scale(const GLfloat *s) const
{
	return scale(s[0], s[1], s[2], s[3]);
}

//! \brief x 軸中心の回転変換を乗じた結果を返す.
//!   \param a 回転角.
//!   \return x 軸中心にさらに a 回転した変換行列.
Matrix rotateX(GLfloat a) const
{
	Matrix m;
	return multiply(m.loadRotateX(a));
}

//! \brief y 軸中心の回転変換を乗じた結果を返す.
//!   \param a 回転角.
//!   \return y 軸中心にさらに a 回転した変換行列.
Matrix rotateY(GLfloat a) const
{
	Matrix m;
	return multiply(m.loadRotateY(a));
}

//! \brief z 軸中心の回転変換を乗じた結果を返す.
//!   \param a 回転角.
//!   \return z 軸中心にさらに a 回転した変換行列.
Matrix rotateZ(GLfloat a) const
{
	Matrix m;
	return multiply(m.loadRotateZ(a));
}

//! \brief (x, y, z) 方向のベクトルを軸とする回転変換を乗じた結果を返す.
//!   \param x 回転軸の x 成分.
//!   \param y 回転軸の y 成分.
//!   \param z 回転軸の z 成分.
//!   \param a 回転角.
//!   \return (x, y, z) を軸にさらに a 回転した変換行列.
Matrix rotate(GLfloat x, GLfloat y, GLfloat z, GLfloat a) const
{
	Matrix m;
	return multiply(m.loadRotate(x, y, z, a));
}

//! \brief r 方向のベクトルを軸とする回転変換を乗じた結果を返す.
//!   \param r 回転軸の方向ベクトルと回転角 (x, y, z).
//!   \param a 回転角.
//!   \return (r[0], r[1], r[2]) を軸にさらに a 回転した変換行列.
Matrix rotate(const GLfloat *r, GLfloat a) const
{
	return rotate(r[0], r[1], r[2], a);
}

//! \brief r 方向のベクトルを軸とする回転の変換行列を乗じた結果を返す.
//!   \param r 回転軸の方向ベクトルと回転角 (x, y, z, a).
//!   \return (r[0], r[1], r[2]) を軸にさらに r[3] 回転した変換行列.
Matrix rotate(const GLfloat *r) const
{
	return rotate(r[0], r[1], r[2], r[3]);
}

//! \brief ビュー変換を乗じた結果を返す.
//!   \param ex 視点の位置の x 座標値.
//!   \param ey 視点の位置の y 座標値.
//!   \param ez 視点の位置の z 座標値.
//!   \param tx 目標点の位置の x 座標値.
//!   \param ty 目標点の位置の y 座標値.
//!   \param tz 目標点の位置の z 座標値.
//!   \param ux 上方向のベクトルの x 成分.
//!   \param uy 上方向のベクトルの y 成分.
//!   \param uz 上方向のベクトルの z 成分.
//!   \return ビュー変換行列を乗じた変換行列.
Matrix lookat(GLfloat ex, GLfloat ey, GLfloat ez,
	GLfloat tx, GLfloat ty, GLfloat tz,
	GLfloat ux, GLfloat uy, GLfloat uz) const
{
	Matrix m;
	return multiply(m.loadLookat(ex, ey, ez, tx, ty, tz, ux, uy, uz));
}

//! \brief ビュー変換を乗じた結果を返す.
//!   \param e 視点の位置の配列変数.
//!   \param t 目標点の位置の配列変数.
//!   \param u 上方向のベクトルのの配列変数.
//!   \return ビュー変換行列を乗じた変換行列.
Matrix lookat(const GLfloat *e, const GLfloat *t, const GLfloat *u) const
{
	return lookat(e[0], e[1], e[2], t[0], t[1], t[2], u[0], u[1], u[2]);
}

//! \brief 直交投影変換を乗じた結果を返す.
//!   \param left ウィンドウの左端の位置.
//!   \param right ウィンドウの右端の位置.
//!   \param bottom ウィンドウの下端の位置.
//!   \param top ウィンドウの上端の位置.
//!   \param zNear 視点から前方面までの位置.
//!   \param zFar 視点から後方面までの位置.
//!   \return 直交投影変換行列を乗じた変換行列.
Matrix orthogonal(GLfloat left, GLfloat right,
	GLfloat bottom, GLfloat top,
	GLfloat zNear, GLfloat zFar) const
{
	Matrix m;
	return multiply(m.loadOrthogonal(left, right, bottom, top, zNear, zFar));
}

//! \brief 透視投影変換を乗じた結果を返す.
//!   \param left ウィンドウの左端の位置.
//!   \param right ウィンドウの右端の位置.
//!   \param bottom ウィンドウの下端の位置.
//!   \param top ウィンドウの上端の位置.
//!   \param zNear 視点から前方面までの位置.
//!   \param zFar 視点から後方面までの位置.
//!   \return 透視投影変換行列を乗じた変換行列.
Matrix frustum(GLfloat left, GLfloat right,
	GLfloat bottom, GLfloat top,
	GLfloat zNear, GLfloat zFar) const
{
	Matrix m;
	return multiply(m.loadFrustum(left, right, bottom, top, zNear, zFar));
}

//! \brief 画角を指定して透視投影変換を乗じた結果を返す.
//!   \param fovy y 方向の画角.
//!   \param aspect 縦横比.
//!   \param zNear 視点から前方面までの位置.
//!   \param zFar 視点から後方面までの位置.
//!   \return 透視投影変換行列を乗じた変換行列.
Matrix perspective(GLfloat fovy, GLfloat aspect,
	GLfloat zNear, GLfloat zFar) const
{
	Matrix m;
	return multiply(m.loadPerspective(fovy, aspect, zNear, zFar));
}

//! \brief 転置行列を返す.
//!   \return 転置行列.
Matrix transpose() const
{
	Matrix t;
	return t.loadTranspose(*this);
}

//! \brief 逆行列を返す.
//!   \return 逆行列.
Matrix invert() const
{
	Matrix t;
	return t.loadInvert(*this);
}

//! \brief 法線変換行列を返す.
//!   \return 法線変換行列.
Matrix normal() const
{
	Matrix t;
	return t.loadNormal(*this);
}

//! \brief ベクトルに対して投影変換を行う.
//!   \param c 変換結果を格納する GLfloat[4] 型の配列.
//!   \param v 元のベクトルの GLfloat[4] 型の配列.
void projection(GLfloat *c, const GLfloat *v) const
{
	projection(c, array, v);
}

//! \brief 変換行列を取り出す.
//!   \return 変換行列を格納した GLfloat[16] 型の配列.
const GLfloat *get() const
{
	return array;
}

//! \brief 変換行列を取り出す.
//!   \param a 変換行列を格納する GLfloat[16] 型の配列.
void get(GLfloat *a) const
{
	for (int i = 0; i < 16; ++i) a[i] = array[i];
}
};

//! \brief 単位行列を返す.
//!   \return 単位行列
inline Matrix Identity()
{
	Matrix t;
	return t.loadIdentity();
};

//! \brief 平行移動の変換行列を返す.
//!   \param x x 方向の移動量.
//!   \param y y 方向の移動量.
//!   \param z z 方向の移動量.
//!   \param w 移動量のスケールファクタ (= 1.0f).
//!   \return 平行移動の変換行列.
inline Matrix Translate(GLfloat x, GLfloat y, GLfloat z, GLfloat w = 1.0f)
{
	Matrix m;
	return m.loadTranslate(x, y, z, w);
}

//! \brief 平行移動の変換行列を返す.
//!   \param t 移動量の GLfloat[4] 型の配列 (x, y, z, w).
//!   \return 平行移動の変換行列
inline Matrix Translate(const GLfloat *t)
{
	Matrix m;
	return m.loadTranslate(t[0], t[1], t[2]);
}

//! \brief 拡大縮小の変換行列を返す.
//!   \param x x 方向の拡大率.
//!   \param y y 方向の拡大率.
//!   \param z z 方向の拡大率.
//!   \param w 拡大率のスケールファクタ (= 1.0f).
//!   \return 拡大縮小の変換行列.
inline Matrix Scale(GLfloat x, GLfloat y, GLfloat z, GLfloat w = 1.0f)
{
	Matrix m;
	return m.loadScale(x, y, z, w);
}

//! \brief 拡大縮小の変換行列を返す.
//!   \param s 拡大率の GLfloat[4] 型の配列 (x, y, z, w).
//!   \return 拡大縮小の変換行列.
inline Matrix Scale(const GLfloat *s)
{
	Matrix m;
	return m.loadScale(s[0], s[1], s[2]);
}

//! \brief x 軸中心の回転の変換行列を返す.
//!   \param a 回転角.
//!   \return x 軸中心に a だけ回転する変換行列.
inline Matrix RotateX(GLfloat a)
{
	Matrix m;
	return m.loadRotateX(a);
}

//! \brief y 軸中心の回転の変換行列を返す.
//!   \param a 回転角.
//!   \return y 軸中心に a だけ回転する変換行列.
inline Matrix RotateY(GLfloat a)
{
	Matrix m;
	return m.loadRotateY(a);
}

//! \brief z 軸中心の回転の変換行列を返す.
//!   \param a 回転角.
//!   \return z 軸中心に a だけ回転する変換行列.
inline Matrix RotateZ(GLfloat a)
{
	Matrix m;
	return m.loadRotateZ(a);
}

//! \brief (x, y, z) 方向のベクトルを軸とする回転の変換行列を乗じた結果を返す.
//!   \param x 回転軸の x 成分.
//!   \param y 回転軸の y 成分.
//!   \param z 回転軸の z 成分.
//!   \param a 回転角.
//!   \return (x, y, z) を軸にさらに a 回転する変換行列.
inline Matrix Rotate(GLfloat x, GLfloat y, GLfloat z, GLfloat a)
{
	Matrix m;
	return m.loadRotate(x, y, z, a);
}

//! \brief r 方向のベクトルを軸とする回転の変換行列を乗じた結果を返す.
//!   \param r 回転軸のベクトルを表す GLfloat[3] 型の配列.
//!   \param a 回転角.
//!   \return r を軸に a だけ回転する変換行列.
inline Matrix Rotate(const GLfloat *r, GLfloat a)
{
	Matrix m;
	return m.loadRotate(r[0], r[1], r[2], a);
}

//! \brief r 方向のベクトルを軸とする回転の変換行列を乗じた結果を返す.
//!   \param r 回転軸のベクトルと回転角を表す GLfloat[4] 型の配列.
//!   \return (r[0], r[1], r[2]) を軸に r[3] だけ回転する変換行列.
inline Matrix Rotate(const GLfloat *r)
{
	Matrix m;
	return m.loadRotate(r[0], r[1], r[2], r[3]);
}

//! \brief ビュー変換行列を返す.
//!   \param ex 視点の位置の x 座標値.
//!   \param ey 視点の位置の y 座標値.
//!   \param ez 視点の位置の z 座標値.
//!   \param tx 目標点の位置の x 座標値.
//!   \param ty 目標点の位置の y 座標値.
//!   \param tz 目標点の位置の z 座標値.
//!   \param ux 上方向のベクトルの x 成分.
//!   \param uy 上方向のベクトルの y 成分.
//!   \param uz 上方向のベクトルの z 成分.
//!   \return 求めたビュー変換行列.
inline Matrix Lookat(
	GLfloat ex, GLfloat ey, GLfloat ez,     // 視点の位置
	GLfloat tx, GLfloat ty, GLfloat tz,     // 目標点の位置
	GLfloat ux, GLfloat uy, GLfloat uz      // 上方向のベクトル
	)
{
	Matrix m;
	return m.loadLookat(ex, ey, ez, tx, ty, tz, ux, uy, uz);
}

//! \brief ビュー変換行列を返す.
//!   \param e 視点の位置の配列変数.
//!   \param t 目標点の位置の配列変数.
//!   \param u 上方向のベクトルのの配列変数.
//!   \return 求めたビュー変換行列.
inline Matrix Lookat(
	const GLfloat *e,                       // 視点の位置
	const GLfloat *t,                       // 目標点の位置
	const GLfloat *u                        // 上方向のベクトル
	)
{
	Matrix m;
	return m.loadLookat(e[0], e[1], e[2], t[0], t[1], t[2], u[0], u[1], u[2]);
}

//! \brief 直交投影変換行列を返す.
//!   \param left ウィンドウの左端の位置.
//!   \param right ウィンドウの右端の位置.
//!   \param bottom ウィンドウの下端の位置.
//!   \param top ウィンドウの上端の位置.
//!   \param zNear 視点から前方面までの位置.
//!   \param zFar 視点から後方面までの位置.
//!   \return 求めた直交投影変換行列.
inline Matrix Orthogonal(GLfloat left, GLfloat right,
	GLfloat bottom, GLfloat top,
	GLfloat zNear, GLfloat zFar)
{
	Matrix m;
	return m.loadOrthogonal(left, right, bottom, top, zNear, zFar);
}

//! \brief 透視透視投影変換行列を返す.
//!   \param left ウィンドウの左端の位置.
//!   \param right ウィンドウの右端の位置.
//!   \param bottom ウィンドウの下端の位置.
//!   \param top ウィンドウの上端の位置.
//!   \param zNear 視点から前方面までの位置.
//!   \param zFar 視点から後方面までの位置.
//!   \return 求めた透視投影変換行列.
inline Matrix Frustum(GLfloat left, GLfloat right,
	GLfloat bottom, GLfloat top,
	GLfloat zNear, GLfloat zFar)
{
	Matrix m;
	return m.loadFrustum(left, right, bottom, top, zNear, zFar);
}

//! \brief 画角を指定して透視投影変換行列を返す.
//!   \param fovy y 方向の画角.
//!   \param aspect 縦横比.
//!   \param zNear 視点から前方面までの位置.
//!   \param zFar 視点から後方面までの位置.
//!   \return 求めた透視投影変換行列.
inline Matrix Perspective(GLfloat fovy, GLfloat aspect,
	GLfloat zNear, GLfloat zFar)
{
	Matrix m;
	return m.loadPerspective(fovy, aspect, zNear, zFar);
}

//! \brief 転置行列を返す.
//!   \param m 元の変換行列.
//!   \return m の転置行列.
inline Matrix Transpose(const Matrix &m)
{
	return m.transpose();
}

//! \brief 逆行列を返す.
//!   \param m 元の変換行列.
//!   \return m の逆行列.
inline Matrix Invert(const Matrix &m)
{
	return m.invert();
}

//! \brief 法線変換行列を返す.
//!   \param m 元の変換行列.
//!   \return m の法線変換行列.
inline Matrix Normal(const Matrix &m)
{
	return m.normal();
}