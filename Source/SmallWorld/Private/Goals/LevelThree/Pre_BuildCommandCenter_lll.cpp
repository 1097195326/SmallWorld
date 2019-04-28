#include "Pre_BuildCommandCenter_lll.h"


float Pre_BuildCommandCenter_lll::Evaluate()
{
	if (mCityActor->GetCommandCenterLevel() > 0)
	{
		return 0.f;
	}
	return 100.f;
}
void Pre_BuildCommandCenter_lll::Enter()
{
	BaseGoal::Enter();

}
GoalState Pre_BuildCommandCenter_lll::Process()
{
	return BaseGoal::Process();

}
void Pre_BuildCommandCenter_lll::End()
{
	BaseGoal::End();

}