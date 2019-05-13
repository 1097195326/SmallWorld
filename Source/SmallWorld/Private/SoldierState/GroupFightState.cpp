#include "GroupFightState.h"
#include "SoldierGroup.h"

GroupFightState::GroupFightState(SoldierGroup * _soldierGroup) :GroupBaseState(_soldierGroup)
{

}
void GroupFightState::OnEnter()
{
	mSoldierGroup->ChangeStateIndex(I_FightIndex);
	mSoldierGroup->UpdateSoldierState();
}
void GroupFightState::OnProcess()
{

}
void GroupFightState::OnEnd()
{

}