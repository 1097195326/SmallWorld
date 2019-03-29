#include "Fig_AttackCity_ll.h"

#include "Fig_ArcherGroup_lll.h"
#include "Fig_FootmanGroup_lll.h"
#include "Fig_GriffinGroup_lll.h"
#include "Fig_HorsemanGroup_lll.h"
#include "Fig_KnightGroup_lll.h"
#include "Fig_MageGroup_lll.h"
#include "Fig_SiegeEngineGroup_lll.h"


Fig_AttackCity_ll::Fig_AttackCity_ll()
{
	BaseGoal * goal = nullptr;
	goal = new Fig_ArcherGroup_lll();
	mCanChooseGoals.push_back(goal);
	goal = new Fig_FootmanGroup_lll();
	mCanChooseGoals.push_back(goal);
	goal = new Fig_GriffinGroup_lll();
	mCanChooseGoals.push_back(goal);
	goal = new Fig_HorsemanGroup_lll();
	mCanChooseGoals.push_back(goal);
	goal = new Fig_KnightGroup_lll();
	mCanChooseGoals.push_back(goal);
	goal = new Fig_MageGroup_lll();
	mCanChooseGoals.push_back(goal);
	goal = new Fig_SiegeEngineGroup_lll();
	mCanChooseGoals.push_back(goal);
}
Fig_AttackCity_ll::~Fig_AttackCity_ll()
{

}
float Fig_AttackCity_ll::Evaluate()
{
	return 0.f;
}
void Fig_AttackCity_ll::Enter()
{
	BaseGoal::Enter();
	mTaskQueun.push(GetBestGoal());
}
GoalState Fig_AttackCity_ll::Process()
{
	return BaseGoal::Process();

}
void Fig_AttackCity_ll::End()
{
	BaseGoal::End();

}