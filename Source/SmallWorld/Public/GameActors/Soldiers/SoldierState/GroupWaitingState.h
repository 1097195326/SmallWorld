#pragma once

#include "GroupBaseState.h"


class GroupWaitingState : public GroupBaseState
{
public:
	GroupWaitingState(SoldierGroup * _soldierGroup);


	virtual void OnEnter() override;
	virtual void OnProcess() override;
	virtual void OnEnd() override;

protected:


private:

};