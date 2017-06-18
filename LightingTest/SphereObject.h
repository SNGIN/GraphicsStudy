#pragma once
#include "ShapeObject.h"

// 球のデータの分割数
#define SLICES 8
#define STACKS 4

// 球のデータの頂点数と面数
#define VERTICES ((SLICES + 1) * (STACKS + 1))
#define FACES (SLICES * STACKS * 2)

class SphereObject:public ShapeObject
{
public:
	SphereObject();
	SphereObject(Vector3 radius, int slices = SLICES, int stacks = STACKS);
	~SphereObject();
};