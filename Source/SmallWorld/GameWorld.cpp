#include "GameWorld.h"
#include "Kismet/GameplayStatics.h"
#include "GameDataManager.h"


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
GameWorld * GameWorld::GetInstance()
{
	static GameWorld world;
	return &world;
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
			TileMap[x][y] = TileStateStruct(x,y,MapActor->AddInstance(FVector(x * TileSize, y * TileSize, 0)));
		}
	}

	int32 EdgeCenter = TileMapSize / 2;



	IsInitialized = true;
}
void GameWorld::ClearCityMap()
{
	

}
ACityActor *  GameWorld::BuildCity(int _x, int _y)
{
	FTransform trans(FVector(_x * CitySize * TitleSize + (CitySize * TitleSize * 0.5), _y * CitySize * TitleSize + (CitySize * TitleSize * 0.5), 0));
	ACityActor * CityActor = Cast<ACityActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(SWI, ACityActor::StaticClass(), trans));
	if (CityActor)
	{


		UGameplayStatics::FinishSpawningActor(CityActor, trans);
		
		//GeneralGoal * goal = new GeneralGoal();
		//goal->InitWithCityActor(CityActor);
		////GeneralGoals.push_back(goal);

		return CityActor;
	}
	return nullptr;
}
void GameWorld::Update()
{

	if (IsInitialized)
	{
		for (auto CityList : CityMap )
		{
			for(auto City : CityList)
			{
				City->On_GameUpdate();
			}
		}
	}
}
bool GameWorld::IsInTileMap(int _index)
{
	return _index >= 0 && _index < TileMapSize;
}
