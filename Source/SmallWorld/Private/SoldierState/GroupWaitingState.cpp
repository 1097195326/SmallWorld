#include "GroupWaitingState.h"
#include "SoldierGroup.h"

GroupWaitingState::GroupWaitingState(SoldierGroup * _soldierGroup) :GroupBaseState(_soldierGroup)
{
	mStateIndex = I_WaitingIndex;

}
void GroupWaitingState::OnEnter()
{
	mSoldierGroup->UpdateSoldierState();
}
void GroupWaitingState::OnProcess()
{

}
void GroupWaitingState::OnEnd()
{

}