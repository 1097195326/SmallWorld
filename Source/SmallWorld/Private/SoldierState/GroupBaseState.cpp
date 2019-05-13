#include "GroupBaseState.h"
#include "SoldierGroup.h"



GroupBaseState::GroupBaseState(SoldierGroup * _soldierGroup):mSoldierGroup(_soldierGroup)
{

}
GroupBaseState::~GroupBaseState()
{
	mSoldierGroup = nullptr;

}
void GroupBaseState::OnEnter()
{

}
void GroupBaseState::OnProcess()
{

}
void GroupBaseState::OnEnd()
{

}