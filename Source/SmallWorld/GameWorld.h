#pragma once

#include "CityActor.h"
#include "SmallWorldInstance.h"
#include "GameWorldActor.h"
#include "GeneralGoal.h"

class GameWorld
{
private:
	GameWorld();
	GameWorld(const GameWorld & _world);
	GameWorld & operator = (const GameWorld & _world);

	// 
	vector<GeneralGoal *>        GeneralGoals;
	vector<vector<ACityActor *>> CityMap;
	AGameWorldActor * GameWorldActor;

public:
	~GameWorld();

	static GameWorld * GetInstance();
	void BuildWorld();

	void  ClearGeneralGoals();

	void	Update();

private:
	bool IsInitialized;

	bool IsInWorld(int _index);
	ACityActor *  BuildCity(int _x, int _y);
};