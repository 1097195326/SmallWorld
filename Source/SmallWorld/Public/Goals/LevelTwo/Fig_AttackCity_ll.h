#pragma once
#include "BaseGoal.h"

class Fig_AttackCity_ll : public BaseGoal
{
public:
	Fig_AttackCity_ll();
	~Fig_AttackCity_ll();

	virtual float  Evaluate()override;
	virtual void Enter()override;
	virtual GoalState Process()override;
	virtual void End() override;
};