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

	USmallWorldInstance * mGameInstance;
	
public:
	~GameWorld();

	static GameWorld * GetInstance();
	void InitWithGameInstance(USmallWorldInstance * _GameInstance);
	void BuildWorld();



};