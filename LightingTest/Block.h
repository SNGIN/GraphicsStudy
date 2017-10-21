#pragma once
#include "Ground.h"
#include "Window.h"
#include "StaticObj.h"
#include "CubeObject.h"
#include "State.h"

//çﬁéøÇÃêF
static GLfloat ambColor[4] = { 0.6f, 0.6f, 0.6f, 1.0f };
static GLfloat diffColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
static GLfloat specColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
static GLfloat shiness = 30.0f;

class Block:public StaticObj
{
private:
	CubeObject* m_Cube;
public:
	Block();
	~Block();

	Block(GLfloat width, GLfloat height, GLfloat depth,Vector3 pos,Physics* a_physics);

	StaticObj* Draw();
	StaticObj* Update();
};

