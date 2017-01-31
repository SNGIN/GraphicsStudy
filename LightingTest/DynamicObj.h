#pragma once

class StaticObject;

//動くオブジェクトの挙動を定義するクラス
class DynamicObj
{
public:
	DynamicObj();
	~DynamicObj();
	void Set(int x, int y);
	void Move();

};

