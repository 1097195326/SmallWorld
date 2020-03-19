#include "Pre_BuildWoodStore_lll.h"


float Pre_BuildWoodStore_lll::Evaluate()
{
	return 	0.f;// mCityActor->GetHouseNum() * lll_Pre_Build_WoodStore - mCityActor->GetWoodStoreNum() * 10;

}
void Pre_BuildWoodStore_lll::Enter()
{
	BaseGoal::Enter();

}
GoalState Pre_BuildWoodStore_lll::Process()
{
	//if (mCityActor->BuildWoodStore())
	{
		return e_Success;
	}
	return e_Fail;

}
void Pre_BuildWoodStore_lll::End()
{
	BaseGoal::End();

}
