#pragma once

#include "CityActor.h"
#include "SmallWorldInstance.h"
#include "GameWorldActor.h"

class GameWorld
{
private:
	GameWorld();
	GameWorld(const GameWorld & _world);
	GameWorld & operator = (const GameWorld & _world);

	// 
	vector<vector<ACityActor *>> CityMap;
	AGameWorldActor * GameWorldActor;

public:
	~GameWorld();

	static GameWorld * GetInstance();
	void BuildWorld();


private:
	bool IsInWorld(int _index);
	ACityActor *  BuildCity(int _x, int _y);
};