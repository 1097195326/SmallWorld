#pragma once

#include "GroupBaseState.h"


class GroupReadyState : public GroupBaseState
{
public:
	GroupReadyState(SoldierGroup * _soldierGroup);


	virtual void OnEnter() override;
	virtual void OnProcess() override;
	virtual void OnEnd() override;

protected:


private:

};