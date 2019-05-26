#include "BaseGroup.h"



BaseGroup::BaseGroup()
{
	mIsFull = false;
	mGroupReadyNum = 0;
}
BaseGroup::~BaseGroup()
{

}
bool BaseGroup::IsFull()
{
	return mIsFull;
}
void BaseGroup::AddGroupNum()
{
	++mGroupReadyNum;
}
void BaseGroup::SubGroupNum()
{
	--mGroupReadyNum;
}