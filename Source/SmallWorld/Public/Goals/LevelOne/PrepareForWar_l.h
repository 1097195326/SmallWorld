#pragma once
#include "BaseGoal.h"

class PrepareForWar_l : public BaseGoal
{
public:
	PrepareForWar_l();
	~PrepareForWar_l();

	virtual float  Evaluate()override;
	virtual void Enter()override;
	virtual GoalState Process()override;
	virtual void End() override;
};