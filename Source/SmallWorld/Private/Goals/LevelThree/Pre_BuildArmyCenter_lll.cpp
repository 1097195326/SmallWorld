#include "Pre_BuildArmyCenter_lll.h"


float Pre_BuildArmyCenter_lll::Evaluate()
{
	if (mCityActor->GetArmyCenterLevel() > 0)
	{
		return 0.f;
	}
	return mCityActor->GetHouseNum() * lll_Pre_Build_ArmyCenter - mCityActor->GetArmyCenterLevel();
}
void Pre_BuildArmyCenter_lll::Enter()
{
	BaseGoal::Enter();

}
GoalState Pre_BuildArmyCenter_lll::Process()
{
	if (mCityActor->BuildArmyCenter())
	{
		return e_Success;
	}
	return e_Fail;

}
void Pre_BuildArmyCenter_lll::End()
{
	BaseGoal::End();

}