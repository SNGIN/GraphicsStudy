#pragma once
#include "ShapeObject.h"

// ���̃f�[�^�̕�����
#define SLICES 8
#define STACKS 4

// ���̃f�[�^�̒��_���Ɩʐ�
#define VERTICES ((SLICES + 1) * (STACKS + 1))
#define FACES (SLICES * STACKS * 2)

class SphereObject:public ShapeObject
{
public:
	SphereObject();
	SphereObject(Vector3 radius, int slices = SLICES, int stacks = STACKS);
	~SphereObject();
};