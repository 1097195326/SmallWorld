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
	BaseGoal * goal = nullptr;
	goal = new Pre_Soldier_Archer_lll();
	mCanChooseGoals.push_back(goal);
	goal = new Pre_Soldier_Footman_lll();
	mCanChooseGoals.push_back(goal);
	goal = new Pre_Soldier_Griffin_lll();
	mCanChooseGoals.push_back(goal);
	goal = new Pre_Soldier_Horseman_lll();
	mCanChooseGoals.push_back(goal);
	goal = new Pre_Soldier_Knight_lll();
	mCanChooseGoals.push_back(goal);
	goal = new Pre_Soldier_Mage_lll();
	mCanChooseGoals.push_back(goal);
	goal = new Pre_Soldier_SiegeEngine_lll();
	mCanChooseGoals.push_back(goal);
}
Pre_Soldiers_ll::~Pre_Soldiers_ll()
{

}
float Pre_Soldiers_ll::Evaluate()
{
	return 0.f;
}
void Pre_Soldiers_ll::Enter()
{
	BaseGoal::Enter();
	mTaskQueun.push(GetBestGoal());
}
GoalState Pre_Soldiers_ll::Process()
{
	return BaseGoal::Process();

}
void Pre_Soldiers_ll::End()
{
	BaseGoal::End();

}