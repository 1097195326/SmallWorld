#include "GroupWaitingState.h"
#include "SoldierGroup.h"

GroupWaitingState::GroupWaitingState(SoldierGroup * _soldierGroup) :GroupBaseState(_soldierGroup)
{

}
void GroupWaitingState::OnEnter()
{
	mSoldierGroup->ChangeStateIndex(I_WaitingIndex);
}
void GroupWaitingState::OnProcess()
{

}
void GroupWaitingState::OnEnd()
{

}