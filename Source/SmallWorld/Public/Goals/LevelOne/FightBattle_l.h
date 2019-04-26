#pragma once
#include "BaseGoal.h"

class FightBattle_l : public BaseGoal
{
public:
	FightBattle_l();
	~FightBattle_l();

	virtual void InitGoals() override;
	virtual float  Evaluate()override;
	virtual void Enter()override;
	virtual GoalState Process()override;
	virtual void End() override;
};