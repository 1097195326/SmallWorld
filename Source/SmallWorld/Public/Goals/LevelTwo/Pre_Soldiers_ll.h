#pragma once
#include "BaseGoal.h"

class Pre_Soldiers_ll : public BaseGoal
{
public:
	Pre_Soldiers_ll();
	~Pre_Soldiers_ll();

	virtual void InitGoals() override;
	virtual float  Evaluate()override;
	virtual void Enter()override;
	virtual GoalState Process()override;
	virtual void End() override;
};