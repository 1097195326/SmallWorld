#pragma once

#include <queue>

enum GoalState
{
	e_Active,
	e_UnActive,
	e_Process,
	e_Fail,
	e_Success,
};
class BaseGoal
{
protected:
	GoalState mState;
	std::queue<BaseGoal *>  mTaskQueun;

public:
	BaseGoal();
	virtual ~BaseGoal();
	
	virtual float  Evaluate();
	void	ClearAllTask();

	virtual void Enter();
	virtual GoalState Process();
	virtual void End();

	GoalState GetState();
};