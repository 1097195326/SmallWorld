#include "GeneralGoal.h"
#include "FightBattle_l.h"
#include "PrepareForWar_l.h"


GeneralGoal::GeneralGoal()
{
	BaseGoal * goal = nullptr;
	goal = new FightBattle_l();
	mCanChooseGoals.push_back(goal);
	goal = new PrepareForWar_l();
	mCanChooseGoals.push_back(goal);
}
GeneralGoal::~GeneralGoal()
{

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