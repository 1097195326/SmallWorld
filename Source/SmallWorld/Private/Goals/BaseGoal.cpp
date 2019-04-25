#include "BaseGoal.h"


BaseGoal::BaseGoal()
{
	mState = e_UnActive;
	mCanChooseGoals.reserve(4);
}
BaseGoal::~BaseGoal()
{
	ClearAllTask();
	ClearAllGoal();
}
BaseGoal * BaseGoal::GetBestGoal()
{
	BaseGoal * bestGoal = nullptr;
	float EvaluateValue = 0.f;

	for (auto goal : mCanChooseGoals)
	{
		float temValue = goal->Evaluate();
		if (temValue > EvaluateValue)
		{
			EvaluateValue = temValue;
			bestGoal = goal;
		}
	}
	return bestGoal;
}
float BaseGoal::Evaluate()
{
	return 0.f;
}
void BaseGoal::Enter()
{
	mState = e_Active;
}
GoalState BaseGoal::Process()
{
	if (mTaskQueun.empty())
	{
		mState = e_Success;
	}
	else
	{
		if (mTaskQueun.front()->GetState() == e_UnActive)
		{
			mTaskQueun.front()->Enter();
		}
		else
		{
			switch (mTaskQueun.front()->Process())
			{
			case e_Fail:
			{
				mState = e_Fail;
				ClearAllTask();
				return mState;
				break;
			}
			case  e_Success:
			{
				mTaskQueun.pop();
				break;
			}
			};
		}
		mState = e_Process;
	}
	return mState;
}
void BaseGoal::End()
{
	mState = e_UnActive;
	
	ClearAllTask();
}
void BaseGoal::ClearAllTask()
{
	while (mTaskQueun.size() > 0)
	{
		mTaskQueun.front()->End();
		mTaskQueun.pop();
	}
}
void BaseGoal::ClearAllGoal()
{
	for (auto goal : mCanChooseGoals)
	{
		delete goal;
	}
	mCanChooseGoals.clear();
}
GoalState BaseGoal::GetState()
{
	return mState;
}