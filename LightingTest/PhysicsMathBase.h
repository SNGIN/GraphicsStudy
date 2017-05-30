#pragma once
#include "Commonheader.h"
#include <assert.h>
#include <stdio.h>
#include <float.h>
#include <windows.h>
#include "vectormath_aos.h"
#include "quat_aos.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define CLAMP(v,a,b) MAX(a,MIN(v,b))
#define PI		3.14159265358979f
#define EPSILON	1e-5f

//TODO:グラフィックス系のもこっちのライブラリを使ったものに書き直す
typedef Vectormath::Aos::Point3     Point3;
typedef Vectormath::Aos::Vector3    Vector3;
typedef Vectormath::Aos::Vector4    Vector4;
typedef Vectormath::Aos::Quat       Quat;
typedef Vectormath::Aos::Matrix3    Matrix3;
typedef Vectormath::Aos::Matrix4    Matrix4;
typedef Vectormath::Aos::Transform3 Transform3;

static inline
float CalcMassBox(float density, const Vector3 &halfExtent)
{
	return density * halfExtent[0] * halfExtent[1] * halfExtent[2] * 8;
}

static inline
Matrix3 CalcInertiaBox(const Vector3 &halfExtent, float mass)
{
	Vector3 sqrSz = halfExtent * 2.0f;
	sqrSz = mulPerElem(sqrSz, sqrSz);
	Matrix3 inertia = Matrix3::identity();
	inertia[0][0] = (mass*(sqrSz[1] + sqrSz[2])) / 12.0f;
	inertia[1][1] = (mass*(sqrSz[0] + sqrSz[2])) / 12.0f;
	inertia[2][2] = (mass*(sqrSz[0] + sqrSz[1])) / 12.0f;
	return inertia;
}

static inline
float CalcMassSphere(float density, float radius)
{
	return (4.0f / 3.0f) * PI * radius * radius * radius * density;
}

static inline
Matrix3 CalcInertiaSphere(float radius, float mass)
{
	Matrix3 inertia = Matrix3::identity();
	inertia[0][0] = inertia[1][1] = inertia[2][2] = 0.4f * mass * radius * radius;
	return inertia;
}
