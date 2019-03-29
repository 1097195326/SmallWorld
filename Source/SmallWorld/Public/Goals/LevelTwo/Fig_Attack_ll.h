#pragma once
#include "BaseGoal.h"

class Fig_Attack_ll : public BaseGoal
{
public:
	Fig_Attack_ll();
	~Fig_Attack_ll();

	virtual float  Evaluate()override;
	virtual void Enter()override;
	virtual GoalState Process()override;
	virtual void End() override;
};