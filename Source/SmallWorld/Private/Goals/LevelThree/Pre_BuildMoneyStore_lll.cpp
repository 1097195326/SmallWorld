#include "Pre_BuildMoneyStore_lll.h"


float Pre_BuildMoneyStore_lll::Evaluate()
{
	return 	mCityActor->GetHouseNum() * lll_Pre_Build_MoneyStore - mCityActor->GetMoneyStoreNum() * 10;
}
void Pre_BuildMoneyStore_lll::Enter()
{
	BaseGoal::Enter();

}
GoalState Pre_BuildMoneyStore_lll::Process()
{
	return BaseGoal::Process();

}
void Pre_BuildMoneyStore_lll::End()
{
	BaseGoal::End();

}