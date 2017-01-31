#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "opengl32.lib")

#pragma once

#include "glew.h"
#include "glfw3.h"
#include "Matrix.h"
#include <cmath>
#include <cfloat>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>

#if !defined(MATH)
#define MATH

class vector2{
	GLfloat m_x, m_y;
public:
	~vector2(){}
	vector2(){}
	vector2(GLfloat x, GLfloat y){ m_x = x; y = m_y; }
	GLfloat x() const { return m_x; }
	GLfloat y() const { return m_y; }

	void set(GLfloat a, GLfloat b){ m_x = a; m_y = b; }
	void setx(GLfloat a){ m_x = a; }
	void sety(GLfloat a){ m_y = a; }
	vector2& operator +=(const vector2 &a) { m_x += a.x(); m_y += a.y(); return *this; }
	vector2& operator -=(const vector2 &a) { m_x -= a.x(); m_y -= a.y(); return *this; }
	vector2& operator /=(const GLfloat &a) { m_x /= a; m_y /= a; return *this; }
	vector2 operator +() const { return *this; }
	vector2 operator -() const { vector2 a(0.0, 0.0); a -= *this; return *this; }
};

static inline vector2 operator +(const vector2 &a, const vector2 &b) { vector2 c = a; c += b; return c; }
static inline vector2 operator -(const vector2 &a, const vector2 &b) { vector2 c = a; c -= b; return c; }
static inline vector2 operator /(const vector2 &a, const GLfloat &b) { vector2 c = a; c /= b; return c; }
static inline bool operator ==(const vector2 &a, const vector2 &b){
	if (a.x() == b.x() && a.y() == b.y()){
		return true;
	}
	else{
		return false;
	}
}

class vector3{
	GLfloat m_x, m_y,m_z;
public:
	~vector3(){}
	vector3(){}
	vector3(GLfloat x, GLfloat y, GLfloat z){ m_x = x; y = m_y; z = m_z; }
	GLfloat x() const { return m_x; }
	GLfloat y() const { return m_y; }
	GLfloat z() const { return m_z; }

	void set(GLfloat a, GLfloat b,GLfloat c){ m_x = a; m_y = b; m_z = c; }
	void setx(GLfloat a){ m_x = a; }
	void sety(GLfloat a){ m_y = a; }
	void setz(GLfloat a){ m_z = a; }
	vector3& operator +=(const vector3 &a) { m_x += a.x(); m_y += a.y(); m_z += a.z(); return *this; }
	vector3& operator -=(const vector3 &a) { m_x -= a.x(); m_y -= a.y(); m_z -= a.z(); return *this; }
	vector3& operator /=(const GLfloat &a) { m_x /= a; m_y /= a; m_z /= a; return *this; }
	vector3 operator +() const { return *this; }
	vector3 operator -() const { vector3 a(0.0, 0.0,0.0); a -= *this; return *this; }
};

static inline vector3 operator +(const vector3 &a, const vector3 &b) { vector3 c = a; c += b; return c; }
static inline vector3 operator -(const vector3 &a, const vector3 &b) { vector3 c = a; c -= b; return c; }
static inline vector3 operator /(const vector3 &a, const GLfloat &b) { vector3 c = a; c /= b; return c; }
static inline bool operator == (const vector3 &a, const vector3 &b){
	if (a.x() == b.x() && a.y() == b.y() && a.z() == b.z()){
		return true;
	}
	else{
		return false;
	}
}

class vector4{
	GLfloat m_x, m_y, m_z, m_w;

public:
	~vector4(){}
	vector4(){}
	vector4(GLfloat x, GLfloat y, GLfloat z, GLfloat w){ m_x = x; y = m_y; z = m_z; w = m_w; }
	GLfloat x() const { return m_x; }
	GLfloat y() const { return m_y; }
	GLfloat z() const { return m_z; }
	GLfloat w() const { return m_w; }

	void set(GLfloat a, GLfloat b, GLfloat c,GLfloat d){ m_x = a; m_y = b; m_z = c; m_w = d; }
	void setx(GLfloat a){ m_x = a; }
	void sety(GLfloat a){ m_y = a; }
	void setz(GLfloat a){ m_z = a; }
	void setw(GLfloat a){ m_w = a; }

};

struct faceData      // 面データ
{
	GLuint p[3];  // 頂点座標番号
	GLuint n[3];  // 頂点法線番号
	GLuint t[3];  // テクスチャ座標番号
	bool smooth;  // スムーズシェーディングの有無
};



#endif

#define DEBUG