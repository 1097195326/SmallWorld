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
	return BaseGoal::Process();

}
void Pre_BuildFoodStore_lll::End()
{
	BaseGoal::End();

}