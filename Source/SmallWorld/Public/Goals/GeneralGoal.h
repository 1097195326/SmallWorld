#pragma once
#include "BaseGoal.h"

class GeneralGoal : public BaseGoal
{
public:
	GeneralGoal();
	~GeneralGoal();

	virtual float  Evaluate()override;
	virtual void Enter()override;
	virtual GoalState Process()override;
	virtual void End() override;
};