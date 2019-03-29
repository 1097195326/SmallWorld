#include "Pre_Building_ll.h"

#include "Pre_BuildBarrack_lll.h"
#include "Pre_BuildCommandCenter_lll.h"
#include "Pre_BuildHouse_lll.h"
#include "Pre_BuildCityWall_lll.h"


Pre_Building_ll::Pre_Building_ll()
{
	BaseGoal * goal = nullptr;
	goal = new Pre_BuildBarrack_lll();
	mCanChooseGoals.push_back(goal);
	goal = new Pre_BuildCommandCenter_lll();
	mCanChooseGoals.push_back(goal);
	goal = new Pre_BuildHouse_lll();
	mCanChooseGoals.push_back(goal);
	goal = new Pre_BuildCityWall_lll();
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