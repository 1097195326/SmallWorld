#include "Pre_BuildArmyCenter_lll.h"


float Pre_BuildArmyCenter_lll::Evaluate()
{
	if (mCityActor->GetArmyCenterLevel() > 0)
	{
		return 0.f;
	}
	return 90.f;
}
void Pre_BuildArmyCenter_lll::Enter()
{
	BaseGoal::Enter();

}
GoalState Pre_BuildArmyCenter_lll::Process()
{
	return BaseGoal::Process();

}
void Pre_BuildArmyCenter_lll::End()
{
	BaseGoal::End();

}