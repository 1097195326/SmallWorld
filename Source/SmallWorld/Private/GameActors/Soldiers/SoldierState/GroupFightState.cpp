#include "GroupFightState.h"
#include "SoldierGroup.h"

GroupFightState::GroupFightState(SoldierGroup * _soldierGroup) :GroupBaseState(_soldierGroup)
{
	mStateIndex = I_FightIndex;
}
void GroupFightState::OnEnter()
{
	mSoldierGroup->UpdateSoldierState();
}
void GroupFightState::OnProcess()
{

}
void GroupFightState::OnEnd()
{

}