#include "PrepareForWar_l.h"
#include "Pre_Building_ll.h"
#include "Pre_Soldiers_ll.h"


PrepareForWar_l::PrepareForWar_l()
{
	BaseGoal * goal = nullptr;
	goal = new Pre_Building_ll();
	mCanChooseGoals.push_back(goal);
	goal = new Pre_Soldiers_ll();
	mCanChooseGoals.push_back(goal);
}
PrepareForWar_l::~PrepareForWar_l()
{

}
float PrepareForWar_l::Evaluate()
{
	return 0.f;
}
void PrepareForWar_l::Enter()
{
	BaseGoal::Enter();
	mTaskQueun.push(GetBestGoal());
}
GoalState PrepareForWar_l::Process()
{
	return BaseGoal::Process();

}
void PrepareForWar_l::End()
{
	BaseGoal::End();

}