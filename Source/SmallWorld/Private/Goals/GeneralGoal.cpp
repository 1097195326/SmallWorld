#include "GeneralGoal.h"
#include "FightBattle_l.h"
#include "PrepareForWar_l.h"


GeneralGoal::GeneralGoal()
{
	
}
GeneralGoal::~GeneralGoal()
{

}
void GeneralGoal::InitGoals()
{
	BaseGoal * goal = nullptr;
	goal = new FightBattle_l();
	goal->InitWithCityActor(mCityActor);
	mCanChooseGoals.push_back(goal);
	goal = new PrepareForWar_l();
	goal->InitWithCityActor(mCityActor);
	mCanChooseGoals.push_back(goal);
}
float GeneralGoal::Evaluate()
{
	return 1.f;
}
void GeneralGoal::Enter()
{
	BaseGoal::Enter();
	mTaskQueun.push(GetBestGoal());
}
GoalState GeneralGoal::Process()
{
	return BaseGoal::Process();

}
void GeneralGoal::End()
{
	BaseGoal::End();

}