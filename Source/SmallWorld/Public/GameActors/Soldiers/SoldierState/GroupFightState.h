#pragma once

#include "GroupBaseState.h"


class GroupFightState : public GroupBaseState
{
public:
	GroupFightState(SoldierGroup * _soldierGroup);


	virtual void OnEnter() override;
	virtual void OnProcess() override;
	virtual void OnEnd() override;

protected:
	

private:

};