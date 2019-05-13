#pragma once

#include "BaseState.h"

enum  GroupStateIndex
{
	I_None,
	I_FightIndex,
	I_ReadyIndex,
	I_WaitingIndex,

};

class SoldierGroup;

class GroupBaseState : public BaseState
{
public:
	GroupBaseState(SoldierGroup * _soldierGroup);
	~GroupBaseState();

	virtual void OnEnter() override;
	virtual void OnProcess() override;
	virtual void OnEnd() override;

protected:
	SoldierGroup * mSoldierGroup;

private:

};