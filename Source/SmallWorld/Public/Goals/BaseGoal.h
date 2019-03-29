#pragma once

#include <queue>
#include <vector>
//#include <math.h>

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
	std::vector<BaseGoal *> mCanChooseGoals;

public:
	BaseGoal();
	virtual ~BaseGoal();
	
	BaseGoal * GetBestGoal();
	void	ClearAllTask();
	void	ClearAllGoal();
	
	virtual float  Evaluate();
	virtual void Enter();
	virtual GoalState Process();
	virtual void End();

	GoalState GetState();
};