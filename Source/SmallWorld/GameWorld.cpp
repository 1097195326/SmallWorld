#include "GameWorld.h"
#include "Kismet/GameplayStatics.h"
#include "GameDataManager.h"
#include "SoldierPawn.h"
#include "BaseBuildingActor.h"
#include "GroundTileActor.h"
#include "CastleTileActor.h"




GameWorld::GameWorld()
{
	IsInitialized = false;
	IsPaused = false;

	GameWorldActor = nullptr;
}
GameWorld::~GameWorld()
{
	GameWorldActor = nullptr;
}
void GameWorld::ScanWorldMap()
{
	UWorld * CurrentWorld = User_GameInstance->GetWorld();
	
	TArray<AActor*> TemActorsArray;
	UGameplayStatics::GetAllActorsOfClass(User_GameInstance, AGroundTileActor::StaticClass(), TemActorsArray);
	for (auto IterActor : TemActorsArray)
	{
		AGroundTileActor * TemActor = Cast<AGroundTileActor>(IterActor);
		GroundActorArray.Add(TemActor);
		TemActor->TrackAround();
	}
	UGameplayStatics::GetAllActorsOfClass(User_GameInstance, ACastleTileActor::StaticClass(), TemActorsArray);
	for (auto IterActor : TemActorsArray)
	{
		ACastleTileActor * TemActor = Cast<ACastleTileActor>(IterActor);
		CastleActorArray.Add(TemActor);
		TemActor->TrackAround();
	}


	IsInitialized = true;
}
void GameWorld::RefreshCloudVisible()
{

	

}
void GameWorld::Update()
{

	if (IsInitialized)
	{
		
	}
}