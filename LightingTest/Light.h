#pragma once
#include "Commonheader.h"

class Light
{
private:
	// ŒõŒ¹
	GLfloat ambLight[4];
	GLfloat diffLight[4];
	GLfloat specLight[4];
	GLfloat position[4];

public:
	Light(){
		ambLight[0] = 0.2; ambLight[1] = 0.2; ambLight[2] = 0.2; ambLight[3] = 1.0;
		diffLight[0] = 0.7; diffLight[1] = 0.7; diffLight[2] = 0.7; diffLight[3] = 0.7;
		specLight[0] = 0.7; specLight[1] = 0.7; specLight[2] = 0.7; specLight[3] = 0.7;
		position[0] = -3.0; position[1] = 4.0; position[2] = 5.0; position[3] = 1.0;

	}
	~Light(){}

	GLfloat* GetAmb(){
		return ambLight;
	}

	GLfloat* GetDiff(){
		return diffLight;
	}

	GLfloat* GetSpec(){
		return specLight;
	}
	GLfloat* GetPos(){
		return position;
	}
};