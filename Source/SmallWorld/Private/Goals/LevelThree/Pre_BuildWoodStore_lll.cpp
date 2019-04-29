#include "Pre_BuildWoodStore_lll.h"


float Pre_BuildWoodStore_lll::Evaluate()
{
	return 	mCityActor->GetHouseNum() * lll_Pre_Build_WoodStore - mCityActor->GetTreeStoreNum() * 10;

}
void Pre_BuildWoodStore_lll::Enter()
{
	BaseGoal::Enter();

}
GoalState Pre_BuildWoodStore_lll::Process()
{
	if (mCityActor->BuildTreeStore())
	{
		return e_Success;
	}
	return e_Fail;

}
void Pre_BuildWoodStore_lll::End()
{
	BaseGoal::End();

}