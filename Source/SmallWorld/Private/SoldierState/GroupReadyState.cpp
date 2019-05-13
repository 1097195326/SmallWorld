#include "GroupReadyState.h"
#include "SoldierGroup.h"

GroupReadyState::GroupReadyState(SoldierGroup * _soldierGroup) :GroupBaseState(_soldierGroup)
{

}
void GroupReadyState::OnEnter()
{
	mSoldierGroup->ChangeStateIndex(I_ReadyIndex);

}
void GroupReadyState::OnProcess()
{

}
void GroupReadyState::OnEnd()
{

}