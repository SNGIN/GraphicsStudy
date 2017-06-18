#include "GameOver.h"
#include "Title.h"
#include "SeaquenceController.h"

GameOver::GameOver()
{
	std::cout << "GameOver" << std::endl;
	mCount = 0;
}


GameOver::~GameOver()
{

}

Boot* GameOver::Update(SeaquenceController*){
	Boot* next = this;
	if (mCount == 60){
		next = new Title;
	}
	++mCount;
	return next;
}