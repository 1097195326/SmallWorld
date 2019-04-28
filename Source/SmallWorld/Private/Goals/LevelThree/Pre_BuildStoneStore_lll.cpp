#include "Pre_BuildStoneStore_lll.h"


float Pre_BuildStoneStore_lll::Evaluate()
{
	return 	mCityActor->GetHouseNum() * lll_Pre_Build_StoneStore - mCityActor->GetStoneStoreNum() * 10;
}
void Pre_BuildStoneStore_lll::Enter()
{
	BaseGoal::Enter();

}
GoalState Pre_BuildStoneStore_lll::Process()
{
	return BaseGoal::Process();

}
void Pre_BuildStoneStore_lll::End()
{
	BaseGoal::End();

}