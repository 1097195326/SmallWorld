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
Fig_Attack_ll::~Fig_Attack_ll()
{

}
float Fig_Attack_ll::Evaluate()
{
	return 0.f;
}
void Fig_Attack_ll::Enter()
{
	BaseGoal::Enter();
	mTaskQueun.push(GetBestGoal());
}
GoalState Fig_Attack_ll::Process()
{
	return BaseGoal::Process();

}
void Fig_Attack_ll::End()
{
	BaseGoal::End();

}