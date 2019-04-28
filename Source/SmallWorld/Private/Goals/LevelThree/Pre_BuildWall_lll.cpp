#include "Pre_BuildWall_lll.h"


float Pre_BuildWall_lll::Evaluate()
{
	if (mCityActor->GetWallLevel() > 0)
	{
		return 0.f;
	}
	return mCityActor->GetHouseNum() * lll_Pre_Build_Wall - mCityActor->GetWallLevel();
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