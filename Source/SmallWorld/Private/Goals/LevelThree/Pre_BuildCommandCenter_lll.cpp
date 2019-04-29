#include "Pre_BuildCommandCenter_lll.h"


float Pre_BuildCommandCenter_lll::Evaluate()
{
	if (mCityActor->GetCommandCenterLevel() > 0)
	{
		return 0.f;
	}
	return lll_Pre_Build_CommandCenter;
}
void Pre_BuildCommandCenter_lll::Enter()
{
	BaseGoal::Enter();

}
GoalState Pre_BuildCommandCenter_lll::Process()
{
	if (mCityActor->BuildCommandCenter())
	{
		return e_Success;
	}
	return e_Fail;

}
void Pre_BuildCommandCenter_lll::End()
{
	BaseGoal::End();

}