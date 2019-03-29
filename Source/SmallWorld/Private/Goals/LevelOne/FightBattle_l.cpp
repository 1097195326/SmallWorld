#include "FightBattle_l.h"
#include "Fig_Attack_ll.h"
#include "Fig_AttackCity_ll.h"
#include "Fig_Defense_ll.h"
#include "Fig_DefenseFromCity_ll.h"


FightBattle_l::FightBattle_l()
{
	BaseGoal * goal = nullptr;
	goal = new Fig_Attack_ll();
	mCanChooseGoals.push_back(goal);
	goal = new Fig_AttackCity_ll();
	mCanChooseGoals.push_back(goal);
	goal = new Fig_Defense_ll();
	mCanChooseGoals.push_back(goal);
	goal = new Fig_DefenseFromCity_ll();
	mCanChooseGoals.push_back(goal);
}
FightBattle_l::~FightBattle_l()
{

}
float FightBattle_l::Evaluate()
{
	return 0.f;
}
void FightBattle_l::Enter()
{
	BaseGoal::Enter();
	mTaskQueun.push(GetBestGoal());
}
GoalState FightBattle_l::Process()
{
	return BaseGoal::Process();

}
void FightBattle_l::End()
{
	BaseGoal::End();

}