#pragma once
#include "Commonheader.h"
#include "InputManager.h"

//シーケンスの元クラス(派生クラスのUpdateを更新していく)
class Boot
{
public:
	virtual ~Boot(){} //なにもしないのでこれでいい
	virtual Boot* Update(Boot*) = 0;
};

