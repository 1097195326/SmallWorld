#include "Pre_BuildStoneStore_lll.h"


float Pre_BuildStoneStore_lll::Evaluate()
{
	return 	0.f;// mCityActor->GetHouseNum() * lll_Pre_Build_StoneStore - mCityActor->GetStoneStoreNum() * 10;
}
void Pre_BuildStoneStore_lll::Enter()
{
	BaseGoal::Enter();

}
GoalState Pre_BuildStoneStore_lll::Process()
{
	/*if (mCityActor->BuildStoneStore())
	{
		return e_Success;
	}*/
	return e_Fail;
}
void Pre_BuildStoneStore_lll::End()
{
	BaseGoal::End();

}