#pragma once
#include "Seaquence.h"
#include "Commonheader.h"
#include "Rect.h"

class SeaquenceController;

//タイトルの挙動を定義する
class Title:public Seaquence
{
public:
	Title();
	~Title();

	Boot* Update(SeaquenceController*);
private:
	Rect* mrect;//タイトル表示に使うRectオブジェト
};