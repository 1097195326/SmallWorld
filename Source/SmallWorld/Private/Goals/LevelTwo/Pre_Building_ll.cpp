#include "Pre_Building_ll.h"

#include "Pre_BuildArmyCenter_lll.h"
#include "Pre_BuildCommandCenter_lll.h"
#include "Pre_BuildHouse_lll.h"
#include "Pre_BuildWall_lll.h"
#include "Pre_BuildBakery_lll.h"
#include "Pre_BuildFarm_lll.h"
#include "Pre_BuildFoodStore_lll.h"
#include "Pre_BuildMoneyStore_lll.h"
#include "Pre_BuildStoneStore_lll.h"
#include "Pre_BuildWoodStore_lll.h"
#include "Pre_BuildMill_lll.h"

Pre_Building_ll::Pre_Building_ll()
{
	BaseGoal * goal = nullptr;
	goal = new Pre_BuildArmyCenter_lll();
	mCanChooseGoals.push_back(goal);
	goal = new Pre_BuildCommandCenter_lll();
	mCanChooseGoals.push_back(goal);
	goal = new Pre_BuildHouse_lll();
	mCanChooseGoals.push_back(goal);
	goal = new Pre_BuildWall_lll();
	mCanChooseGoals.push_back(goal);
	goal = new Pre_BuildBakery_lll();
	mCanChooseGoals.push_back(goal);
	goal = new Pre_BuildFarm_lll();
	mCanChooseGoals.push_back(goal);
	goal = new Pre_BuildFoodStore_lll();
	mCanChooseGoals.push_back(goal);
	goal = new Pre_BuildMoneyStore_lll();
	mCanChooseGoals.push_back(goal);
	goal = new Pre_BuildStoneStore_lll();
	mCanChooseGoals.push_back(goal);
	goal = new Pre_BuildWoodStore_lll();
	mCanChooseGoals.push_back(goal);
	goal = new Pre_BuildMill_lll();
	mCanChooseGoals.push_back(goal);

}
Pre_Building_ll::~Pre_Building_ll()
{

}
float Pre_Building_ll::Evaluate()
{
	return 0.f;
}
void Pre_Building_ll::Enter()
{
	BaseGoal::Enter();
	mTaskQueun.push(GetBestGoal());
}
GoalState Pre_Building_ll::Process()
{
	return BaseGoal::Process();

}
void Pre_Building_ll::End()
{
	BaseGoal::End();

}