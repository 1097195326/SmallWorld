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
		BuildingData->SpawnBuildingActor(User_GameInstance->GetWorld(), CastleTileActor->GetActorTransform());
	}

}
void GameManager::RefreshCloudVisible()
{

	

}
void GameManager::Tick(float DeltaTime)
{
	if (IsInitialized)
	{
		

		ProgressManager::GetInstance()->Tick(DeltaTime);

	}
}