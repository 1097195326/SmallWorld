#include "Fig_Attack_ll.h"
#include "Fig_ArcherGroup_lll.h"
#include "Fig_FootmanGroup_lll.h"
#include "Fig_GriffinGroup_lll.h"
#include "Fig_HorsemanGroup_lll.h"
#include "Fig_KnightGroup_lll.h"
#include "Fig_MageGroup_lll.h"
#include "Fig_SiegeEngineGroup_lll.h"


Fig_Attack_ll::Fig_Attack_ll()
{
	
}
Fig_Attack_ll::~Fig_Attack_ll()
{

}
void Fig_Attack_ll::InitGoals()
{
	BaseGoal * goal = nullptr;
	goal = new Fig_ArcherGroup_lll();
	goal->InitWithCityActor(mCityActor);
	mCanChooseGoals.push_back(goal);
	goal = new Fig_FootmanGroup_lll();
	goal->InitWithCityActor(mCityActor);
	mCanChooseGoals.push_back(goal);
	goal = new Fig_GriffinGroup_lll();
	goal->InitWithCityActor(mCityActor);
	mCanChooseGoals.push_back(goal);
	goal = new Fig_HorsemanGroup_lll();
	goal->InitWithCityActor(mCityActor);
	mCanChooseGoals.push_back(goal);
	goal = new Fig_KnightGroup_lll();
	goal->InitWithCityActor(mCityActor);
	mCanChooseGoals.push_back(goal);
	goal = new Fig_MageGroup_lll();
	goal->InitWithCityActor(mCityActor);
	mCanChooseGoals.push_back(goal);
	goal = new Fig_SiegeEngineGroup_lll();
	goal->InitWithCityActor(mCityActor);
	mCanChooseGoals.push_back(goal);
}
float Fig_Attack_ll::Evaluate()
{
	return 0.f;
}
void Fig_Attack_ll::Enter()
{
	BaseGoal::Enter();
	BaseGoal * goal = GetBestGoal();
	goal->Enter();
	mTaskQueun.push(goal);
}
GoalState Fig_Attack_ll::Process()
{
	return BaseGoal::Process();

}
void Fig_Attack_ll::End()
{
	BaseGoal::End();

}