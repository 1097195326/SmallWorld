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

	void StartGame();
	void EndGame();

	void ScanWorldMap();
	void BuildGameWorld();
	void RefreshCloudVisible();
	void Tick(float DeltaTime);

	static void GetGroundTileAroundSoldier(AGroundTileActor* InMainTile, int32 InDistance, TArray<class AGroundTileActor*>& OutTiles, bool InContainSoldier = false);
	static void GetGroundTilesWithCondition(const TArray<AGroundTileActor*> & InTiles, TArray<class AGroundTileActor*>& OutTiles, ASoldierPawn * InSoldier, bool InContainFriend, bool InContainEnemy, bool InContainNoSoldier);
	static void GetGroundTilesFarCastle(FIntVector CastleLocation, AGroundTileActor* InMainTile, const TArray<AGroundTileActor*> & InTiles, TArray<class AGroundTileActor*>& OutTiles);
	static TArray<TileMapStruct> GetGroundTilesNearSoldiers(const TArray<AGroundTileActor*> & InTiles, int32 InDistance, ASoldierPawn * InSoldier, bool InIsEnemy = true);
	static AGroundTileActor * GetGroundTileWithSoldiersNum(const TArray<TileMapStruct> & InArrayTileMap, bool InMore = true);
	static AGroundTileActor * GetGroundTileWithDistance(AGroundTileActor* InMainTile, const TArray<AGroundTileActor*> & InTiles, bool InFar = true);

	FVector GetForwardVector();

	ATargetPoint * PlayerTargetPoint;
	ATargetPoint * EnemyTargetPoint;
	ATargetPoint * CameraTargetPoint;
private:
	TMap<int32 ,TMap<int32,class AGroundTileActor*>>	GroundActorArray;
	TArray<class AGroundTileActor*> CurrentVisibleGroundArray;

	AGameWorldActor * GameWorldActor;

	bool IsInitialized;
	bool IsPaused;


};