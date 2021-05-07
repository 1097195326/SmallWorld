#include "GameManager.h"
#include "Kismet/KismetMathLibrary.h"
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
	GroundActorArray.Empty();

	UWorld * CurrentWorld = User_GameInstance->GetWorld();
	
	TArray<AActor*> TemActorsArray;
	UGameplayStatics::GetAllActorsOfClass(User_GameInstance, AGroundTileActor::StaticClass(), TemActorsArray);
	for (auto IterActor : TemActorsArray)
	{
		AGroundTileActor * TemActor = Cast<AGroundTileActor>(IterActor);
		int32 SignX = TemActor->GetSignXIndex();
		int32 SignY = TemActor->GetSignYIndex();
		if (GroundActorArray.Contains(SignY))
		{
			TMap<int32, AGroundTileActor*> * FindMap = GroundActorArray.Find(SignY);
			FindMap->Add(SignX, TemActor);
		}
		else
		{
			TMap<int32, AGroundTileActor*> & AddMap = GroundActorArray.Add(SignY, TMap<int32, AGroundTileActor*>());
			AddMap.Add(SignX, TemActor);
		}
		TemActor->TrackAround();
	}

	GroundActorArray.KeySort([](int32 A, int32 B) {return A < B; });
	for (auto IterArray : GroundActorArray)
	{
		UE_LOG(LogTemp, Log, TEXT("zhx for ground actor-------------------------- :num:%d"), IterArray.Value.Num());
		IterArray.Value.KeySort([](int32 A, int32 B) {return A < B; });
		for (auto IterActor : IterArray.Value)
		{
			UE_LOG(LogTemp, Log, TEXT("zhx for ground actor : y = %d,x = %d"), IterActor.Value->GetSignYIndex(), IterActor.Value->GetSignXIndex());
		}
	}

	UGameplayStatics::GetAllActorsOfClass(User_GameInstance, ATargetPoint::StaticClass(), TemActorsArray);
	for (AActor * IterActor : TemActorsArray)
	{
		if (IterActor->Tags.Contains(FName(TEXT("Player"))))
		{
			PlayerTargetPoint = Cast<ATargetPoint>(IterActor);
		}else if (IterActor->Tags.Contains(FName(TEXT("Enemy"))))
		{
			EnemyTargetPoint = Cast<ATargetPoint>(IterActor);
		}
	}

}
void GameManager::BuildGameWorld()
{
	HordeDataClass * HordeData = nullptr;
	FTransform  SpawnTransform;
	if (PlayerTargetPoint)
	{
		SpawnTransform = PlayerTargetPoint->GetActorTransform();
		RaceEnum UserRace = GameDataManager::GetInstance()->GetUserData()->GetCurrentRace();
		HordeData = GameDataManager::GetInstance()->GetGameWorldData()->CreateHordeData(UserRace);
		GameDataManager::GetInstance()->GetUserData()->SetHordeData(HordeData);
		BaseBuildingDataClass *	 BuildingData = HordeData->SpawnBuildingData("CommandCenter");
		ABaseBuildingActor * BuildingActor = BuildingData->SpawnBuildingActor(User_GameInstance->GetWorld(), SpawnTransform, 0);
	}
	if (EnemyTargetPoint)
	{
		SpawnTransform = EnemyTargetPoint->GetActorTransform();
		RaceEnum TemRace = Race_Orc;// (RaceEnum)UKismetMathLibrary::RandomIntegerInRange(Race_Human, Race_Undead);
		HordeData = GameDataManager::GetInstance()->GetGameWorldData()->CreateHordeData(TemRace);
		BaseBuildingDataClass *	 BuildingData = HordeData->SpawnBuildingData("CommandCenter");
		ABaseBuildingActor * BuildingActor = BuildingData->SpawnBuildingActor(User_GameInstance->GetWorld(), SpawnTransform, 0);
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

void GameManager::GetGroundTileAroundSoldier(class AGroundTileActor* InMainTile, int32 InDistance, TArray<class AGroundTileActor*>& OutTiles, bool InContainSoldier)
{
	if (InMainTile == nullptr) { return; }
	for (int i = 1; i <= InDistance; i++)
	{
		for (int32 j = AGroundTileActor::Direction_Forward; j < AGroundTileActor::Direction_Num; j++)
		{
			AGroundTileActor* TemTile = InMainTile->GetAroundTileActorByDistance(i, (AGroundTileActor::DirectionEnum)j,InContainSoldier);
			if (TemTile)
			{
				OutTiles.AddUnique(TemTile);
			}
		}
	}
}
void GameManager::GetGroundTilesWithCondition(const TArray<AGroundTileActor *> & InTiles, TArray<class AGroundTileActor *>& OutTiles, ASoldierPawn * InSoldier,bool InContainFriend, bool InContainEnemy,bool InContainNoSoldier)
{
	/*for (AGroundTileActor * IterTile : InTiles)
	{
		if (IterTile->IsHaveGameActor())
		{
			ASoldierPawn * OnTileSoldier = IterTile->GetGameActors()[0];
			if (InContainFriend && !OnTileSoldier->IsEnemy(InSoldier) && !IterTile->IsHaveFlySoldier())
			{
				OutTiles.AddUnique(IterTile);
			}else if (InContainEnemy && OnTileSoldier->IsEnemy(InSoldier))
			{
				OutTiles.AddUnique(IterTile);
			}
		}else if (InContainNoSoldier)
		{
			OutTiles.AddUnique(IterTile);
		}
	}*/
}
TArray<TileMapStruct>  GameManager::GetGroundTilesNearSoldiers(const TArray<AGroundTileActor*> & InTiles, int32 InDistance, ASoldierPawn * InSoldier, bool InIsEnemy)
{
	TArray<TileMapStruct>  ArrayTileMap;
	//for (AGroundTileActor * IterTile : InTiles)
	//{
	//	TileMapStruct  TileMap;
	//	TileMap.MainTile = IterTile;
	//	for (int i = 1; i <= InDistance; i++)
	//	{
	//		for (int32 j = AGroundTileActor::Direction_Forward; j < AGroundTileActor::Direction_Num; j++)
	//		{
	//			AGroundTileActor* TemTile = IterTile->GetAroundTileActorByDistance(i, (AGroundTileActor::DirectionEnum)j, true);
	//			//AGroundTileActor* TemTile = IterTile->GetHaveSoldierAroundTileActorByDistance(i, (AGroundTileActor::DirectionEnum)j, true);
	//			if (TemTile && TemTile->IsHaveGameActor())
	//			{
	//				ASoldierPawn * OnTileSoldier = TemTile->GetGameActors()[0];
	//				if ((InIsEnemy && OnTileSoldier->IsEnemy(InSoldier)) ||
	//					(!InIsEnemy && !OnTileSoldier->IsEnemy(InSoldier))
	//					)
	//				{
	//					TileMap.AroundTile.AddUnique(TemTile);
	//				}
	//			}
	//		}
	//	}
	//	if (TileMap.AroundTile.Num() > 0)
	//	{
	//		ArrayTileMap.Add(TileMap);
	//	}
	//}
	return ArrayTileMap;
}
AGroundTileActor * GameManager::GetGroundTileWithSoldiersNum(const TArray<TileMapStruct> & InArrayTileMap, bool InMore /* = true */)
{
	AGroundTileActor * ResTile = nullptr;
	const TileMapStruct * PreTileMap = nullptr;
	for (const TileMapStruct & IterMap : InArrayTileMap)
	{
		if (PreTileMap == nullptr)
		{
			PreTileMap = &IterMap;
		}
		if (InMore)
		{
			if (IterMap.AroundTile.Num() > PreTileMap->AroundTile.Num())
			{
				PreTileMap = &IterMap;
			}
		}
		else
		{
			if (IterMap.AroundTile.Num() < PreTileMap->AroundTile.Num())
			{
				PreTileMap = &IterMap;
			}
		}
	}
	if (PreTileMap != nullptr)
	{
		ResTile = PreTileMap->MainTile;
	}
	return ResTile;
}
void GameManager::GetGroundTilesFarCastle(FIntVector CastleLocation, AGroundTileActor* InMainTile, const TArray<AGroundTileActor *> & InTiles, TArray<class AGroundTileActor *>& OutTiles)
{
	FIntVector MainTileLocation = (FIntVector)InMainTile->GetActorLocation();
	FIntVector MainTileFromCastle = MainTileLocation - CastleLocation;
	for (AGroundTileActor * IterTile : InTiles)
	{
		FIntVector VDistance = (FIntVector)IterTile->GetActorLocation() - CastleLocation;
		if ((FMath::Abs(VDistance.X) + FMath::Abs(VDistance.Y)) > (FMath::Abs(MainTileFromCastle.X) + FMath::Abs(MainTileFromCastle.Y)))
		{
			OutTiles.Add(IterTile);
		}
	}
}
AGroundTileActor * GameManager::GetGroundTileWithDistance(AGroundTileActor* InMainTile, const TArray<AGroundTileActor *> & InTiles, bool InFar /* = true */)
{
	FIntVector MainTileLocation = (FIntVector)InMainTile->GetActorLocation();
	AGroundTileActor * ResTile = nullptr;
	int32 IDistance = 0;
	TArray<AGroundTileActor*> EqualDistanceTiles;
	for (AGroundTileActor * IterTile : InTiles)
	{
		FIntVector VDistance = (FIntVector)IterTile->GetActorLocation() - MainTileLocation;
		int32 IterDistance = VDistance.X + VDistance.Y;
		if (IDistance == 0)
		{
			IDistance = IterDistance;
			ResTile = IterTile;
			continue;
		}
		if (IDistance == IterDistance)
		{
			EqualDistanceTiles.Add(IterTile);
		}
		else
		{
			if (InFar)
			{
				if (IterDistance > IDistance)
				{
					IDistance = IterDistance;
					ResTile = IterTile;
					EqualDistanceTiles.Empty();
					EqualDistanceTiles.Add(IterTile);
				}
			}
			else
			{
				if (IterDistance < IDistance)
				{
					IDistance = IterDistance;
					ResTile = IterTile;
					EqualDistanceTiles.Empty();
					EqualDistanceTiles.Add(IterTile);
				}
			}
		}
	}
	int32 NumEqualDis = EqualDistanceTiles.Num();
	if (NumEqualDis > 1)
	{
		int32 RandIndex = UKismetMathLibrary::RandomInteger(NumEqualDis);
		ResTile = EqualDistanceTiles[RandIndex];
	}
	return ResTile;
}