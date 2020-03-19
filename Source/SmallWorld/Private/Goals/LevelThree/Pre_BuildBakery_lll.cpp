#include "Pre_BuildBakery_lll.h"


float Pre_BuildBakery_lll::Evaluate()
{
	return 	0.f;// mCityActor->GetHouseNum() * lll_Pre_Build_Bakery - mCityActor->GetBakeryNum();
}
void Pre_BuildBakery_lll::Enter()
{
	BaseGoal::Enter();

}
GoalState Pre_BuildBakery_lll::Process()
{
	/*if (mCityActor->BuildBakery())
	{
		return e_Success;
	}*/
	return e_Fail;

}
void Pre_BuildBakery_lll::End()
{
	BaseGoal::End();

}