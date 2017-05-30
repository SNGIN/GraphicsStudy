#pragma once
#include "PhysicsMathBase.h"

static inline void CalcTangentVector(const Vector3 &normal, Vector3 &tangent1, Vector3 &tangent2)
{
	Vector3 vec(1.0f, 0.0f, 0.0f);
	Vector3 n(normal);
	n[0] = 0.0f;
	if (lengthSqr(n) < EPSILON) {
		vec = Vector3(0.0f, 1.0f, 0.0f);
	}
	tangent1 = normalize(cross(normal, vec));
	tangent2 = normalize(cross(tangent1, normal));
}