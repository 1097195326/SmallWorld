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
	

}
Pre_Building_ll::~Pre_Building_ll()
{

}
void Pre_Building_ll::InitGoals()
{
	BaseGoal * goal = nullptr;
	goal = new Pre_BuildArmyCenter_lll();
	goal->InitWithCityActor(mCityActor);
	mCanChooseGoals.push_back(goal);
	goal = new Pre_BuildCommandCenter_lll();
	goal->InitWithCityActor(mCityActor);
	mCanChooseGoals.push_back(goal);
	goal = new Pre_BuildHouse_lll();
	goal->InitWithCityActor(mCityActor);
	mCanChooseGoals.push_back(goal);
	goal = new Pre_BuildWall_lll();
	goal->InitWithCityActor(mCityActor);
	mCanChooseGoals.push_back(goal);
	goal = new Pre_BuildBakery_lll();
	goal->InitWithCityActor(mCityActor);
	mCanChooseGoals.push_back(goal);
	goal = new Pre_BuildFarm_lll();
	goal->InitWithCityActor(mCityActor);
	mCanChooseGoals.push_back(goal);
	goal = new Pre_BuildFoodStore_lll();
	goal->InitWithCityActor(mCityActor);
	mCanChooseGoals.push_back(goal);
	goal = new Pre_BuildMoneyStore_lll();
	goal->InitWithCityActor(mCityActor);
	mCanChooseGoals.push_back(goal);
	goal = new Pre_BuildStoneStore_lll();
	goal->InitWithCityActor(mCityActor);
	mCanChooseGoals.push_back(goal);
	goal = new Pre_BuildWoodStore_lll();
	goal->InitWithCityActor(mCityActor);
	mCanChooseGoals.push_back(goal);
	goal = new Pre_BuildMill_lll();
	goal->InitWithCityActor(mCityActor);
	mCanChooseGoals.push_back(goal);
}
float Pre_Building_ll::Evaluate()
{
	
	return 1.f;
}
void Pre_Building_ll::Enter()
{
	BaseGoal::Enter();
	BaseGoal * goal = GetBestGoal();
	goal->Enter();
	mTaskQueun.push(goal);
}
GoalState Pre_Building_ll::Process()
{
	return BaseGoal::Process();

}
void Pre_Building_ll::End()
{
	BaseGoal::End();

}