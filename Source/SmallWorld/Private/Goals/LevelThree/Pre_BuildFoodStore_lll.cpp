#include "Pre_BuildFoodStore_lll.h"


float Pre_BuildFoodStore_lll::Evaluate()
{
	return 	mCityActor->GetHouseNum() * lll_Pre_Build_FoodStore - mCityActor->GetFoodStoreNum() * 10;
}
void Pre_BuildFoodStore_lll::Enter()
{
	BaseGoal::Enter();

}
GoalState Pre_BuildFoodStore_lll::Process()
{
	if (mCityActor->BuildFoodStore())
	{
		return e_Success;
	}
	return e_Fail;

}
void Pre_BuildFoodStore_lll::End()
{
	BaseGoal::End();

}