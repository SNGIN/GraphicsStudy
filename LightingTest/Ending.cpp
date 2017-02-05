#include "Ending.h"
#include "Commonheader.h"
#include "Title.h"

Ending::Ending()
{

	std::cout << "Ending" << std::endl;
}


Ending::~Ending()
{
	//イメージリソースの解放
	//Common::Delete();
}

Boot* Ending::Update(SeaquenceController*){
	Boot* next = this;
	if (mCount == 120){
		next = new Title;
	}
	//描画

	++mCount;
	return next;
}
