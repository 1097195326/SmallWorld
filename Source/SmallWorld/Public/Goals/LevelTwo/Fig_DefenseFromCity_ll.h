#pragma once
#include "BaseGoal.h"

class Fig_DefenseFromCity_ll : public BaseGoal
{
public:
	Fig_DefenseFromCity_ll();
	~Fig_DefenseFromCity_ll();

	virtual void InitGoals() override;
	virtual float  Evaluate()override;
	virtual void Enter()override;
	virtual GoalState Process()override;
	virtual void End() override;
};