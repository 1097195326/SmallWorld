#include "GroupReadyState.h"
#include "SoldierGroup.h"

GroupReadyState::GroupReadyState(SoldierGroup * _soldierGroup) :GroupBaseState(_soldierGroup)
{
	mStateIndex = I_ReadyIndex;
}
void GroupReadyState::OnEnter()
{
	mSoldierGroup->UpdateSoldierState();

}
void GroupReadyState::OnProcess()
{

}
void GroupReadyState::OnEnd()
{

}