#include "Pre_BuildWall_lll.h"


float Pre_BuildWall_lll::Evaluate()
{
	if (mCityActor->GetWallLevel() > 0)
	{
		return 0.f;
	}
	return 50.f;
}
void Pre_BuildWall_lll::Enter()
{
	BaseGoal::Enter();

}
GoalState Pre_BuildWall_lll::Process()
{
	return BaseGoal::Process();

}
void Pre_BuildWall_lll::End()
{
	BaseGoal::End();

}