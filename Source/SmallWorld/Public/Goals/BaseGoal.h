#pragma once

#include <queue>
#include <vector>
#include "CityActor.h"
//#include <math.h>

enum GoalState
{
	e_Active,
	e_UnActive,
	e_Process,
	e_Fail,
	e_Success,
};
// one level
const float l_Fight = 0.4f;
const float l_Prepare = 0.6f;
// two level
const float ll_Fig_Attack = 0.f;
const float ll_Fig_AttackCity = 0.f;
const float ll_Fig_Defense = 0.f;
const float ll_Fig_DefenseFromCity = 0.f;

const float ll_Pre_Building = 0.5f;
const float ll_Pre_Soldiers = 0.5f;

//three level
const float lll_Pre_Build_House = 0.5f;
const float lll_Pre_Build_Farm = 0.4f;
const float lll_Pre_Build_MoneyStore = 0.3f;
const float lll_Pre_Build_StoneStore = 0.3f;
const float lll_Pre_Build_WoodStore = 0.3f;
const float lll_Pre_Build_FoodStore = 0.3f;
const float lll_Pre_Build_Wall = 0.2f;
const float lll_Pre_Build_ArmyCenter = 0.2f;
const float lll_Pre_Build_Mill = 0.1f;
const float lll_Pre_Build_Bakery = 0.1f;

const float lll_Pre_Soldier_Archer = 0.2f;
const float lll_Pre_Soldier_Footman = 0.2f;
const float lll_Pre_Soldier_Griffin = 0.1f;
const float lll_Pre_Soldier_Horseman = 0.1f;
const float lll_Pre_Soldier_Knight = 0.2f;
const float lll_Pre_Soldier_Mage = 0.1f;
const float lll_Pre_Soldier_SiegeEngine = 0.f;


class BaseGoal
{
protected:
	GoalState mState;
	std::queue<BaseGoal *>  mTaskQueun;
	std::vector<BaseGoal *> mCanChooseGoals;

	ACityActor * mCityActor;
public:
	BaseGoal();
	virtual ~BaseGoal();
	
	void InitWithCityActor(ACityActor * _cityActor);
	virtual void InitGoals();
	ACityActor * GetSelfCityActor();

	BaseGoal * GetBestGoal();
	void	ClearAllTask();
	void	ClearAllGoal();
	
	virtual float  Evaluate();
	virtual void Enter();
	virtual GoalState Process();
	virtual void End();

	GoalState GetState();
};