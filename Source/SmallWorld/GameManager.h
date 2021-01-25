#pragma once

#include "GameWorldActor.h"

class ASoldierPawn;
class ABaseBuildingActor;
class AGroundTileActor;

struct TileMapStruct
{
	AGroundTileActor * MainTile;
	TArray<AGroundTileActor*>  AroundTile;
};

class GameManager : public SingleTemplateClass<GameManager>
{
public:
	GameManager();
	~GameManager();

	void ScanWorldMap();
	void BuildGameWorld();
	void RefreshCloudVisible();
	void Tick(float DeltaTime);

	static void GetGroundTileAroundSoldier(AGroundTileActor* InMainTile, int32 InDistance, TArray<class AGroundTileActor*>& OutTiles, bool InContainSoldier = false);
	static TArray<TileMapStruct> GetGroundTilesHaveSoldier(const TArray<AGroundTileActor*> & InTiles, int32 InDistance, ASoldierPawn * InSoldier, bool InIsEnemy = true);
	static AGroundTileActor * GetGroundTileWithSoldiersNum(const TArray<TileMapStruct> & InArrayTileMap, bool InMore = true);
	static AGroundTileActor * GetGroundTileWithDistance(AGroundTileActor* InMainTile, const TArray<AGroundTileActor*> & InTiles, bool InFar = true);

private:
	TArray<class AGroundTileActor*>	GroundActorArray;
	TArray<class AGroundTileActor*> CurrentVisibleGroundArray;
	TArray<class ACastleTileActor*>	CastleActorArray;

	AGameWorldActor * GameWorldActor;

	bool IsInitialized;
	bool IsPaused;


};