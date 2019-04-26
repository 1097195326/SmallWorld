#pragma once
#include "BaseGoal.h"

class Fig_Defense_ll : public BaseGoal
{
public:
	Fig_Defense_ll();
	~Fig_Defense_ll();
	
	virtual void InitGoals() override;
	virtual float  Evaluate()override;
	virtual void Enter()override;
	virtual GoalState Process()override;
	virtual void End() override;
};