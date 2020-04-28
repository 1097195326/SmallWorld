#include "GroupAutoFightState.h"
#include "SoldierGroup.h"

GroupAutoFightState::GroupAutoFightState(SoldierGroup * _soldierGroup) :GroupBaseState(_soldierGroup)
{
	mStateIndex = I_AutoFightIndex;
}
void GroupAutoFightState::OnEnter()
{
	mSoldierGroup->UpdateSoldierState();
}
void GroupAutoFightState::OnProcess()
{

}
void GroupAutoFightState::OnEnd()
{

}