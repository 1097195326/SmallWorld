#pragma once

#include "BuildingActors/CityActor.h"
#include "SmallWorldInstance.h"
#include "GameWorldActor.h"
#include "MapActor.h"

class ASoldierPawn;
class ABaseBuildingActor;

struct CoordStruct
{
	int32	IndexX;
	int32	IndexY;

	~CoordStruct() { IndexX = -1; IndexY = -1; }
	CoordStruct() :IndexX(-1), IndexY(-1) {}
	CoordStruct(int32 InX, int32 InY) :IndexX(InX), IndexY(InY) {}
	CoordStruct(const CoordStruct & InCoord) :IndexX(InCoord.IndexX), IndexY(InCoord.IndexY) {}
	CoordStruct(CoordStruct && InCoord) :IndexX(std::move(InCoord.IndexX)), IndexY(std::move(InCoord.IndexY)) {}
	CoordStruct & operator = (const CoordStruct & InCoord) { IndexX = InCoord.IndexX; IndexY = InCoord.IndexY; return *this; }
	CoordStruct & operator = (CoordStruct && InCoord) { IndexX = std::move(InCoord.IndexX); IndexY = std::move(InCoord.IndexY); return *this; }
	bool operator == (const CoordStruct & InCoord) { return (IndexX == InCoord.IndexX && IndexY == InCoord.IndexY); }

	CoordStruct Left() { return CoordStruct(IndexX, IndexY - 1); }
	CoordStruct Right() { return CoordStruct(IndexX, IndexY + 1); }
	CoordStruct Up() { return CoordStruct(IndexX + 1, IndexY); }
	CoordStruct Down() { return CoordStruct(IndexX - 1, IndexY); }
};
struct TileStateStruct
{
	CoordStruct Coord;
	int32 InstanceIndex;

	ASoldierPawn *	SoldierPawn;
	ABaseBuildingActor * BuildingActor;

	~TileStateStruct() { InstanceIndex = -1; SoldierPawn = nullptr; BuildingActor = nullptr; }
	TileStateStruct() :Coord(-1, -1), InstanceIndex(-1), SoldierPawn(nullptr), BuildingActor(nullptr) {}
	TileStateStruct(int32 InX, int32 InY, int32 InIndex) :Coord(InX, InY), InstanceIndex(InIndex), SoldierPawn(nullptr), BuildingActor(nullptr) {}
	TileStateStruct(const TileStateStruct & InTile) :Coord(InTile.Coord), InstanceIndex(InTile.InstanceIndex), SoldierPawn(InTile.SoldierPawn), BuildingActor(InTile.BuildingActor) {}
	TileStateStruct(TileStateStruct && InTile) :Coord(std::move(InTile.Coord)), InstanceIndex(std::move(InTile.InstanceIndex)), SoldierPawn(std::move(InTile.SoldierPawn)), BuildingActor(std::move(InTile.BuildingActor)) {}
	TileStateStruct & operator = (const TileStateStruct & InTile) { Coord = InTile.Coord; InstanceIndex = InTile.InstanceIndex; SoldierPawn = InTile.SoldierPawn; BuildingActor = InTile.BuildingActor; return *this; }
	TileStateStruct & operator = (TileStateStruct && InTile) { Coord = std::move(InTile.Coord); InstanceIndex = std::move(InTile.InstanceIndex); SoldierPawn = std::move(InTile.SoldierPawn); BuildingActor = std::move(InTile.BuildingActor); return *this; }

	bool IsHavePawn() { return SoldierPawn != nullptr; }
	void SoldierEnter(ASoldierPawn * InSoldier) { SoldierPawn = InSoldier; }
	void SoldierExit() { SoldierPawn = nullptr; }

	bool IsHaveBuilding() { return BuildingActor != nullptr; }
	void BuildingEnter(ABaseBuildingActor * InBuilding) { BuildingActor = InBuilding; }
	void BuildingExit() { BuildingActor = nullptr; }
};
struct TileGroupStruct
{
	//TMap<CoordStruct,TileStateStruct>	TileMap;




};


class GameWorld
{
private:

	GameWorld();


	TileStateStruct TileMap[TileMapSize][TileMapSize];

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