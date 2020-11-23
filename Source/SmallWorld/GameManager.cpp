#include "GameManager.h"
#include "Kismet/GameplayStatics.h"
#include "UserGameInstance.h"
#include "SoldierPawn.h"
#include "BaseBuildingActor.h"
#include "GroundTileActor.h"
#include "CastleTileActor.h"
#include "Kismet/KismetMathLibrary.h"
#include "ProgressManager.h"
#include "GameDataManager.h"
#include "UIControllerManager.h"



GameManager::GameManager()
{
	IsInitialized = false;
	IsPaused = false;

	GameWorldActor = nullptr;
}
GameManager::~GameManager()
{
	GameWorldActor = nullptr;
}
void GameManager::ScanWorldMap()
{
	UWorld * CurrentWorld = User_GameInstance->GetWorld();
	
	TArray<AActor*> TemActorsArray;
	UGameplayStatics::GetAllActorsOfClass(User_GameInstance, AGroundTileActor::StaticClass(), TemActorsArray);
	FString  OGIStr;
	for (auto IterActor : TemActorsArray)
	{
		AGroundTileActor * TemActor = Cast<AGroundTileActor>(IterActor);
		GroundActorArray.Add(TemActor);
		TemActor->TrackAround();
		OGIStr += TemActor->GetObjectId().ToString();
	}
	UGameplayStatics::GetAllActorsOfClass(User_GameInstance, ACastleTileActor::StaticClass(), TemActorsArray);
	for (auto IterActor : TemActorsArray)
	{
		ACastleTileActor * TemActor = Cast<ACastleTileActor>(IterActor);
		CastleActorArray.Add(TemActor);
		TemActor->TrackAround();
	}

}
void GameManager::BuildGameWorld()
{
	for (int32 i = 0; i < CastleActorArray.Num(); i++)
	{
		ACastleTileActor * CastleTileActor = CastleActorArray[i];
		HordeDataClass * HordeData = nullptr;
		if (i == 0)
		{
			RaceEnum UserRace = GameDataManager::GetInstance()->GetUserData()->GetCurrentRace();
			HordeData = GameDataManager::GetInstance()->GetGameWorldData()->CreateHordeData(UserRace);
			GameDataManager::GetInstance()->GetUserData()->SetHordeData(HordeData);
		}
		else
		{
			RaceEnum TemRace = (RaceEnum)UKismetMathLibrary::RandomIntegerInRange(Race_Human, Race_Undead);
			HordeData = GameDataManager::GetInstance()->GetGameWorldData()->CreateHordeData(TemRace);
		}
		BaseBuildingDataClass *	 BuildingData = HordeData->SpawnBuildingData("CommandCenter");
		ABaseBuildingActor * BuildingActor = BuildingData->SpawnBuildingActor(User_GameInstance->GetWorld(), CastleTileActor->GetActorTransform());
		if (BuildingActor)
		{
			BuildingActor->SetCastleTileActor(CastleTileActor);
		}
	}

}
void GameManager::RefreshCloudVisible()
{

	

}
void GameManager::Tick(float DeltaTime)
{
	//if (IsInitialized)
	{
		

		ProgressManager::GetInstance()->Tick(DeltaTime);
		UIControllerManager::GetInstance()->Tick(DeltaTime);
	}
}

void GameManager::GetGroundTileAroundSoldier(class ASoldierPawn* InSoldier, int32 InDistance, class AGroundTileActor* & OutMainTile, TArray<class AGroundTileActor *>& OutTiles)
{
	OutMainTile = InSoldier->GetGroundTile();
	for (int i = 1; i <= InDistance; i++)
	{
		for (int32 j = AGroundTileActor::Direction_Forward; j < AGroundTileActor::Direction_Other; j++)
		{
			AGroundTileActor* TemTile = OutMainTile->GetAroundTileActorByDistance(i, (AGroundTileActor::DirectionEnum)j);
			if (TemTile)
			{
				OutTiles.Add(TemTile);
			}
		}
	}
}