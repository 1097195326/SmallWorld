#include "TGeneralGoal.h"
//#include "FightBattle_l.h"
//#include "PrepareForWar_l.h"

/*
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
	BaseGoal * goal = GetBestGoal();
	goal->Enter();
	mTaskQueun.push(goal);
}
GoalState GeneralGoal::Process()
{
	mState = BaseGoal::Process();
	if (mState == e_Success || mState == e_Fail)
	{
		End();
	}
	return mState;
}
void GeneralGoal::End()
{
	BaseGoal::End();

}*/