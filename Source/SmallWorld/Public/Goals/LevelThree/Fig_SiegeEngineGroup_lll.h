#pragma once
#include "BaseGoal.h"

class Fig_SiegeEngineGroup_lll : public BaseGoal
{
public:
	virtual float  Evaluate()override;
	virtual void Enter()override;
	virtual GoalState Process()override;
	virtual void End() override;
};