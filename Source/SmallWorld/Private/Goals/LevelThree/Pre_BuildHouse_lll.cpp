#include "Pre_BuildHouse_lll.h"


float Pre_BuildHouse_lll::Evaluate()
{
	return lll_Pre_Build_House;
}
void Pre_BuildHouse_lll::Enter()
{
	BaseGoal::Enter();

}
GoalState Pre_BuildHouse_lll::Process()
{
	if (mCityActor->BuildHouse())
	{
		return e_Success;
	}
	return e_Fail;
}
void Pre_BuildHouse_lll::End()
{
	BaseGoal::End();

}