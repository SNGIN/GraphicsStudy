#pragma once
#include "ShapeObject.h"

// ���̃f�[�^�̕�����
#define SLICES 64
#define STACKS 32

// ���̃f�[�^�̒��_���Ɩʐ�
#define VERTICES ((SLICES + 1) * (STACKS + 1))
#define FACES (SLICES * STACKS * 2)

class SphereObject:public ShapeObject
{
private:
	GLfloat pv[VERTICES][3];
	GLfloat nv[VERTICES][3];
	GLfloat tv[VERTICES][2];
	GLuint face[FACES][3];

public:
	SphereObject();
	SphereObject(float radius, int slices = SLICES, int stacks = STACKS);
	~SphereObject();
	void Draw();
};