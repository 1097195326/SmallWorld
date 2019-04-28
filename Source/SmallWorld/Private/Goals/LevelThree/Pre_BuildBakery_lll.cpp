#include "Pre_BuildBakery_lll.h"


float Pre_BuildBakery_lll::Evaluate()
{
	return 	mCityActor->GetHouseNum() * lll_Pre_Build_Bakery - mCityActor->GetBakeryNum();
}
void Pre_BuildBakery_lll::Enter()
{
	BaseGoal::Enter();

}
GoalState Pre_BuildBakery_lll::Process()
{
	return BaseGoal::Process();

}
void Pre_BuildBakery_lll::End()
{
	BaseGoal::End();

}