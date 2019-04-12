#pragma once

#include "CityActor.h"


class GameWorld
{
private:
	GameWorld();
	GameWorld(const GameWorld & _world);
	GameWorld & operator = (const GameWorld & _world);

	// 
	vector<vector<ACityActor *>> CityMap;


public:
	~GameWorld();

	static GameWorld * GetInstance();

	void BuildWorld();



};