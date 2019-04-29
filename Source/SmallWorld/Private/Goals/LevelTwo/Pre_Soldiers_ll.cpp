#include "Pre_Soldiers_ll.h"

#include "Pre_Soldier_Archer_lll.h"
#include "Pre_Soldier_Footman_lll.h"
#include "Pre_Soldier_Griffin_lll.h"
#include "Pre_Soldier_Horseman_lll.h"
#include "Pre_Soldier_Knight_lll.h"
#include "Pre_Soldier_Mage_lll.h"
#include "Pre_Soldier_SiegeEngine_lll.h"


Pre_Soldiers_ll::Pre_Soldiers_ll()
{
	
}
Pre_Soldiers_ll::~Pre_Soldiers_ll()
{

}
void Pre_Soldiers_ll::InitGoals()
{
	BaseGoal * goal = nullptr;
	goal = new Pre_Soldier_Archer_lll();
	goal->InitWithCityActor(mCityActor);
	mCanChooseGoals.push_back(goal);
	goal = new Pre_Soldier_Footman_lll();
	goal->InitWithCityActor(mCityActor);
	mCanChooseGoals.push_back(goal);
	goal = new Pre_Soldier_Griffin_lll();
	goal->InitWithCityActor(mCityActor);
	mCanChooseGoals.push_back(goal);
	goal = new Pre_Soldier_Horseman_lll();
	goal->InitWithCityActor(mCityActor);
	mCanChooseGoals.push_back(goal);
	goal = new Pre_Soldier_Knight_lll();
	goal->InitWithCityActor(mCityActor);
	mCanChooseGoals.push_back(goal);
	goal = new Pre_Soldier_Mage_lll();
	goal->InitWithCityActor(mCityActor);
	mCanChooseGoals.push_back(goal);
	goal = new Pre_Soldier_SiegeEngine_lll();
	goal->InitWithCityActor(mCityActor);
	mCanChooseGoals.push_back(goal);
}
float Pre_Soldiers_ll::Evaluate()
{
	return 0.f;
}
void Pre_Soldiers_ll::Enter()
{
	BaseGoal::Enter();
	BaseGoal * goal = GetBestGoal();
	goal->Enter();
	mTaskQueun.push(goal);
}
GoalState Pre_Soldiers_ll::Process()
{
	return BaseGoal::Process();

}
void Pre_Soldiers_ll::End()
{
	BaseGoal::End();

}