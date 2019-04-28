#include "Pre_BuildFarm_lll.h"


float Pre_BuildFarm_lll::Evaluate()
{
	return mCityActor->GetHouseNum() * lll_Pre_Build_Farm - mCityActor->GetFarmNum();
}
void Pre_BuildFarm_lll::Enter()
{
	BaseGoal::Enter();

}
GoalState Pre_BuildFarm_lll::Process()
{
	return BaseGoal::Process();

}
void Pre_BuildFarm_lll::End()
{
	BaseGoal::End();

}