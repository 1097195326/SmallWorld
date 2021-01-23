#pragma once

#include "GameWorldActor.h"

class ASoldierPawn;
class ABaseBuildingActor;
class AGroundTileActor;

class GameManager : public SingleTemplateClass<GameManager>
{
public:
	GameManager();
	~GameManager();

	void ScanWorldMap();
	void BuildGameWorld();
	void RefreshCloudVisible();
	void Tick(float DeltaTime);

	static void GetGroundTileAroundSoldier(class AGroundTileActor* InMainTile, int32 InDistance, TArray<class AGroundTileActor*>& OutTiles, bool InContainSoldier = false);
	static void GetGroundTilesHaveSoldier(const TArray<AGroundTileActor*> & InTiles, int32 InDistance, TArray<class AGroundTileActor*>& OutTiles);
	static void GetGroundTileFarOtherSoldier(const TArray<AGroundTileActor*> & InTiles, int32 InDistance, TArray<class AGroundTileActor*>& OutTiles, bool InIsEnemy = true);

private:
	TArray<class AGroundTileActor*> CurrentVisibleGroundArray;
	TArray<class AGroundTileActor*>	GroundActorArray;
	TArray<class ACastleTileActor*>	CastleActorArray;

	AGameWorldActor * GameWorldActor;

	bool IsInitialized;
	bool IsPaused;


};