#pragma once
#include "Seaquence.h"
#include "Commonheader.h"

class SeaquenceController;

//タイトルの挙動を定義する
class Title:public Seaquence
{
public:
	Title();
	~Title();

	Boot* Update(SeaquenceController*);
private:
	//タイトル画面のイメージ保持
};