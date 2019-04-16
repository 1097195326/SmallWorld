#pragma once

#include "CityActor.h"
#include "SmallWorldInstance.h"


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


private:
	bool IsInWorld(int _index);
	ACityActor *  BuildCity(int _x, int _y);
};