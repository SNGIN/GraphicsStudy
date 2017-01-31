#include "StaticObj.h"


StaticObj::StaticObj() :mFlags(0)
{
}


StaticObj::~StaticObj()
{
}

void StaticObj::SetFlag(unsigned f){

}

bool StaticObj::CheckFlag(unsigned f)const{
	return (mFlags & f) ? true : false;
}