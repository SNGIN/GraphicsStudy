#pragma once

//静的オブジェクトを管理するクラス
class StaticObj
{
public:
	StaticObj();
	~StaticObj();
	enum ObjFlag
	{
		FLAG_WALL = (1 << 0),
		FLAG_GOAL = (1 << 1),
	};
	bool CheckFlag(unsigned)const;
	void SetFlag(unsigned);
	void ResetFlag(unsigned);
private:
	unsigned mFlags;
};

