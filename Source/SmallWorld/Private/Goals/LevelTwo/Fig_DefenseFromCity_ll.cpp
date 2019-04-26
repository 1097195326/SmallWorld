#include "Fig_DefenseFromCity_ll.h"

#include "Fig_ArcherGroup_lll.h"
#include "Fig_FootmanGroup_lll.h"
#include "Fig_GriffinGroup_lll.h"
#include "Fig_HorsemanGroup_lll.h"
#include "Fig_KnightGroup_lll.h"
#include "Fig_MageGroup_lll.h"
#include "Fig_SiegeEngineGroup_lll.h"


Fig_DefenseFromCity_ll::Fig_DefenseFromCity_ll()
{
	
}
Fig_DefenseFromCity_ll::~Fig_DefenseFromCity_ll()
{

}
void Fig_DefenseFromCity_ll::InitGoals()
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
float Fig_DefenseFromCity_ll::Evaluate()
{
	return 0.f;
}
void Fig_DefenseFromCity_ll::Enter()
{
	BaseGoal::Enter();
	mTaskQueun.push(GetBestGoal());
}
GoalState Fig_DefenseFromCity_ll::Process()
{
	return BaseGoal::Process();

}
void Fig_DefenseFromCity_ll::End()
{
	BaseGoal::End();

}