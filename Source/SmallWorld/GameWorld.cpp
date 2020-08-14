#include "GameWorld.h"
#include "Kismet/GameplayStatics.h"
#include "GameDataManager.h"
#include "SoldierPawn.h"
#include "BaseBuildingActor.h"


GameWorld::GameWorld()
{
	IsInitialized = false;
	IsPaused = false;

	GameWorldActor = nullptr;
	MapActor = nullptr;
}
GameWorld::~GameWorld()
{
	GameWorldActor = nullptr;
	MapActor = nullptr;
}
void GameWorld::BuildTileWorld()
{
	// Build Gameworld Actor
	FTransform WorldTrans(FVector(TileMapSize * TileSize * 0.5f - TileSize * 0.5f, TileMapSize * TileSize * 0.5f - TileSize * 0.5f, 0));
	GameWorldActor = Cast<AGameWorldActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(SWI, AGameWorldActor::StaticClass(), WorldTrans));
	if (GameWorldActor)
	{
		UGameplayStatics::FinishSpawningActor(GameWorldActor, WorldTrans);
	}
	FTransform MapTrans(FVector(0,0,0));
	MapActor = Cast<AMapActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(SWI, AMapActor::StaticClass(), MapTrans));
	if (MapActor)
	{
		FAssetData GroundMeshData = GameDataManager::GetInstance()->GetBuildingAssetDataByIconName(TEXT("GroundTileMesh"));
		MapActor->GroundMeshComponent->SetStaticMesh(Cast<UStaticMesh>(GroundMeshData.GetAsset()));
		FAssetData CloudMeshData = GameDataManager::GetInstance()->GetBuildingAssetDataByIconName(TEXT("CloudTileMesh"));
		MapActor->CloudMeshComponent->SetStaticMesh(Cast<UStaticMesh>(CloudMeshData.GetAsset()));
		MapActor->ReregisterAllComponents();
		UGameplayStatics::FinishSpawningActor(MapActor, MapTrans);
	}

	// Build Map
	for (int x = 0; x < TileMapSize ; x++)
	{
		for (int y = 0; y < TileMapSize; y++)
		{
			TileMap[x][y] = TileStateStruct(x,y,MapActor->AddGroupInstance(FVector(x * TileSize, y * TileSize, 0)));
		}
	}

	CoordStruct  MapCenter(TileMapSize / 2, TileMapSize / 2);
	CoordStruct  BottomPos(MapCenter.IndexX, MapCenter.IndexY - (TileMapSize / 2 - 1));
	CoordStruct  UpPos(MapCenter.IndexX, MapCenter.IndexY + (TileMapSize / 2 - 1));
	CoordStruct  RightPos(MapCenter.IndexX + (TileMapSize / 2 - 1), MapCenter.IndexY);
	CoordStruct  LeftPos(MapCenter.IndexX - (TileMapSize / 2 - 1), MapCenter.IndexY);

	CastleArray.Add(TileStateStruct(BottomPos.IndexX, BottomPos.IndexY, MapActor->AddCastleInstance(FVector(BottomPos.IndexX * TileSize, BottomPos.IndexY * TileSize, 0), (FVector(MapCenter.IndexX, MapCenter.IndexY, 0) - FVector(BottomPos.IndexX, BottomPos.IndexY, 0)).ToOrientationRotator())));
	CastleArray.Add(TileStateStruct(UpPos.IndexX, UpPos.IndexY, MapActor->AddCastleInstance(FVector(UpPos.IndexX * TileSize, UpPos.IndexY * TileSize, 0), (FVector(MapCenter.IndexX, MapCenter.IndexY, 0) - FVector(UpPos.IndexX, UpPos.IndexY, 0)).ToOrientationRotator())));
	CastleArray.Add(TileStateStruct(RightPos.IndexX, RightPos.IndexY, MapActor->AddCastleInstance(FVector(RightPos.IndexX * TileSize, RightPos.IndexY * TileSize, 0), (FVector(MapCenter.IndexX, MapCenter.IndexY, 0) - FVector(RightPos.IndexX, RightPos.IndexY, 0)).ToOrientationRotator())));
	CastleArray.Add(TileStateStruct(LeftPos.IndexX, LeftPos.IndexY, MapActor->AddCastleInstance(FVector(LeftPos.IndexX * TileSize, LeftPos.IndexY * TileSize, 0), (FVector(MapCenter.IndexX, MapCenter.IndexY, 0) - FVector(LeftPos.IndexX, LeftPos.IndexY, 0)).ToOrientationRotator())));
	

	IsInitialized = true;
}
void GameWorld::Update()
{

	if (IsInitialized)
	{
		
	}
}
bool GameWorld::IsInTileMap(const int32 & InIndex)
{
	return InIndex >= 0 && InIndex < TileMapSize;
}
bool GameWorld::IsInTileMap(const CoordStruct& InCoord)
{
	return IsInTileMap(InCoord.IndexX) && IsInTileMap(InCoord.IndexY);
}
bool GameWorld::GetTileByCoord(const CoordStruct& InCoord,TileStateStruct & OutTile)
{
	if (IsInTileMap(InCoord))
	{
		OutTile = TileMap[InCoord.IndexX][InCoord.IndexY];
		return true;
	}
	return false;
}
int32 GameWorld::GetMinMovePower(const TArray<TileStateStruct> & InTileArray)
{
	int32 TemMovePower = 0;
	for (const auto & TemTile : InTileArray)
	{
		if (TemTile.IsHavePawn())
		{
			int32 SoliderMovePower = TemTile.SoldierPawn->GetSoldierData()->GetMovePower();
			if (SoliderMovePower < TemMovePower) { TemMovePower = SoliderMovePower; }
			else if (TemMovePower == 0) { TemMovePower = SoliderMovePower; }
		}
	}
	return MoveTemp(TemMovePower);
}
int32 GameWorld::GetMinMoveDistance(const TArray<TileStateStruct> & InTileArray)
{
	int32 TemMoveDistance = 0;
	for (const auto & TemTile : InTileArray)
	{
		if (TemTile.IsHavePawn())
		{
			int32 SoliderMoveDistance = TemTile.SoldierPawn->GetSoldierData()->GetMoveDistance();
			if (SoliderMoveDistance < TemMoveDistance) { TemMoveDistance = SoliderMoveDistance; }
			else if (TemMoveDistance == 0){TemMoveDistance = SoliderMoveDistance;}
		}
	}
	return MoveTemp(TemMoveDistance);
}
TArray<TileStateStruct> GameWorld::GetCanArriveTileArray(const TArray<TileStateStruct> & InTileArray,const int32 & InMoveDistance)
{
	TArray<TileStateStruct> TemArray;

	

	return TemArray;
}