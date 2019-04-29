#include "FightBattle_l.h"
#include "Fig_Attack_ll.h"
#include "Fig_AttackCity_ll.h"
#include "Fig_Defense_ll.h"
#include "Fig_DefenseFromCity_ll.h"


FightBattle_l::FightBattle_l()
{
	
}
FightBattle_l::~FightBattle_l()
{

}
void FightBattle_l::InitGoals()
{
	BaseGoal * goal = nullptr;
	goal = new Fig_Attack_ll();
	goal->InitWithCityActor(mCityActor);
	mCanChooseGoals.push_back(goal);
	goal = new Fig_AttackCity_ll();
	goal->InitWithCityActor(mCityActor);
	mCanChooseGoals.push_back(goal);
	goal = new Fig_Defense_ll();
	goal->InitWithCityActor(mCityActor);
	mCanChooseGoals.push_back(goal);
	goal = new Fig_DefenseFromCity_ll();
	goal->InitWithCityActor(mCityActor);
	mCanChooseGoals.push_back(goal);
}
float FightBattle_l::Evaluate()
{
	return 0.f;
}
void FightBattle_l::Enter()
{
	BaseGoal::Enter();
	BaseGoal * goal = GetBestGoal();
	goal->Enter();
	mTaskQueun.push(goal);
}
GoalState FightBattle_l::Process()
{
	return BaseGoal::Process();

}
void FightBattle_l::End()
{
	BaseGoal::End();

}