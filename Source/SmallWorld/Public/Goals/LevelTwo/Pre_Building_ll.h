#pragma once
#include "BaseGoal.h"

class Pre_Building_ll : public BaseGoal
{
public:
	Pre_Building_ll();
	~Pre_Building_ll();

	virtual float  Evaluate()override;
	virtual void Enter()override;
	virtual GoalState Process()override;
	virtual void End() override;
};