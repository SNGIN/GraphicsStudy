#pragma once
#include "PhysicsMathBase.h"

struct Constraint{
	Vector3 axis;//�S����
	float jacDiagInv;//�S�����̕���
	float rhs;//�����S����
	float lowerLimit;//�S���͂̉���
	float upperLimit;//�S���͂̏��
	float accumImpulse;//�~�ς����S����
};