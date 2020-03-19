#include "Pre_BuildMill_lll.h"


float Pre_BuildMill_lll::Evaluate()
{
	return 	0.f;// mCityActor->GetHouseNum() * lll_Pre_Build_Mill - mCityActor->GetMillNum();
}
void Pre_BuildMill_lll::Enter()
{
	BaseGoal::Enter();

}
GoalState Pre_BuildMill_lll::Process()
{
	/*if (mCityActor->BuildMill())
	{
		return e_Success;
	}*/
	return e_Fail;

}
void Pre_BuildMill_lll::End()
{
	BaseGoal::End();

}