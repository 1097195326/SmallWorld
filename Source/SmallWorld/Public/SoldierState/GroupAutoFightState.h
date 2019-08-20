#pragma once


#include "GroupBaseState.h"


class GroupAutoFightState : public GroupBaseState
{
public:
	GroupAutoFightState(SoldierGroup * _soldierGroup);


	virtual void OnEnter() override;
	virtual void OnProcess() override;
	virtual void OnEnd() override;

protected:


private:

};