#pragma once
#include "Commonheader.h"

class StaticObject;

//動くオブジェクトの挙動を定義するクラス
class DynamicObj
{
protected:
	vector3 position;
public:
	DynamicObj();
	~DynamicObj();
	vector3 Get();
	void Set(GLfloat x, GLfloat y);
	virtual DynamicObj* Draw(){ return 0; };
	virtual DynamicObj* Update(){ return 0; };
};

