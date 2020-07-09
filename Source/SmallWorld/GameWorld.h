#pragma once

#include "BuildingActors/CityActor.h"
#include "SmallWorldInstance.h"
#include "GameWorldActor.h"
#include "MapActor.h"
#include "Soldiers/SoldierPawn.h"

using namespace TileGameConfig;


struct TileStruct 
{
	int32 IndexX;
	int32 IndexY;
	int32 InstanceIndex;
	ASoldierPawn *	SoldierPawn;
	TileStruct():
		IndexX(-1),
		IndexY(-1),
		InstanceIndex(-1),
		SoldierPawn(nullptr)
	{}
	bool IsHavePawn() { return SoldierPawn != nullptr; }
};

class GameWorld
{
private:

	GameWorld();


	int32 TileMap[TileMapSize][TileMapSize];

	vector<vector<ACityActor *>>	CityMap;
	AGameWorldActor *				GameWorldActor;
	AMapActor *						MapActor;
public:
	~GameWorld();

	static GameWorld *				GetInstance();
	void							BuildTileWorld();

	void							ClearCityMap();

	void							Update();

private:
	bool							IsInitialized;
	bool							IsPaused;

	bool							IsInTileMap(int _index);
	ACityActor *					BuildCity(int _x, int _y);
};