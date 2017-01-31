#include "GameOver.h"
#include "Title.h"
#include "SeaquenceController.h"

GameOver::GameOver()
{

}


GameOver::~GameOver()
{

}

Boot* GameOver::Update(SeaquenceController*){
	Boot* next = this;
	if (mCount == 60){
		next = new Title;
	}
	//•`‰æ
	std::cout << "GameOver" << std::endl;

	++mCount;
	return next;
}