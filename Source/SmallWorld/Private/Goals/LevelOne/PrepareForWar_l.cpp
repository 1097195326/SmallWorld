#include "PrepareForWar_l.h"
#include "Pre_Building_ll.h"
#include "Pre_Soldiers_ll.h"


PrepareForWar_l::PrepareForWar_l()
{
	
}
PrepareForWar_l::~PrepareForWar_l()
{

}
void PrepareForWar_l::InitGoals()
{
	BaseGoal * goal = nullptr;
	goal = new Pre_Building_ll();
	goal->InitWithCityActor(mCityActor);
	mCanChooseGoals.push_back(goal);
	goal = new Pre_Soldiers_ll();
	goal->InitWithCityActor(mCityActor);
	mCanChooseGoals.push_back(goal);
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