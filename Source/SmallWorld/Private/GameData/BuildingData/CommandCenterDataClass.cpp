
#include "CommandCenterDataClass.h"
#include "CommandCenterActor.h"
#include "Kismet/KismetMathLibrary.h"
#include "GroundTileActor.h"
#include "CastleTileActor.h"


G_REGISTER_CLASS(CommandCenterDataClass)

CommandCenterDataClass::CommandCenterDataClass()
{
	BuildingType = B_CommandCenter;
}
CommandCenterDataClass::~CommandCenterDataClass()
{
    
}
void CommandCenterDataClass::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("CommandCenterDataClass");
	BaseBuildingDataClass::Serialization(Writer);

		Writer->WriteObjectStart("SoldiersData");
		for (auto data : SoldiersMap)
		{
			data.Value->Serialization(Writer);
		}
		Writer->WriteObjectEnd();//SoldiersData

	Writer->WriteObjectEnd();// CommandCenterDataClass
    
}
void CommandCenterDataClass::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
    
    
}
ABaseBuildingActor * CommandCenterDataClass::SpawnBuildingActor(UWorld * world, const FTransform & SpawnTF, const int32 && InIndex)
{
	FActorSpawnParameters Paramerter;
	Paramerter.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	BuildingActor = world->SpawnActor<ACommandCenterActor>(ACommandCenterActor::StaticClass(), SpawnTF, Paramerter);
	FString MeshName = FString::Printf(TEXT("Mesh%s%d"), *BuildingName, InIndex);
	if (BuildingActor && BuildingActor->SetMeshComponentByIconName(MeshName))
	{
		BuildingActor->SetBuildingData(this);
	}
	return BuildingActor;
}
void CommandCenterDataClass::TrySpawnSoldier()
{
	TArray<AGroundTileActor*>  TileArray = BuildingActor->GetCastleTileActor()->GetAroundActors();
	int32 TileIndex = UKismetMathLibrary::RandomInteger(TileArray.Num());
	FVector SpLocation = FVector::ZeroVector;
	AGroundTileActor * GroundTile = TileArray[TileIndex];
	if (GroundTile->GetSoldiers().Num() > 0)
	{
		for (auto IterTile : TileArray)
		{
			if (IterTile->GetSoldiers().Num() == 0)
			{
				SpLocation = IterTile->GetActorLocation();
				GroundTile = IterTile;
				break;
			}
		}
	}
	else
	{
		SpLocation = GroundTile->GetActorLocation();
	}
	if (SpLocation != FVector::ZeroVector)
	{
		SoldierTypeEnum SoldierType = (SoldierTypeEnum)UKismetMathLibrary::RandomIntegerInRange(Soldier_Archer, Soldier_SiegeEngine);

		ASoldierPawn * SoldierPawn = SpawnSoldier(SoldierType);
		if (SoldierPawn)
		{
			SoldierPawn->SetActorLocationAndRotation(SpLocation + FVector(0, 0, 100), BuildingActor->GetActorRotation());
			GroundTile->AddSoldier(SoldierPawn);
			SoldierPawn->SetOriginGroundTile(GroundTile);
			SoldierPawn->SetMoveLocation(SpLocation);
		}
	}
}
ASoldierPawn * CommandCenterDataClass::SpawnSoldier(SoldierTypeEnum InType)
{
	FString  SoldierName;
	switch (InType)
	{
	case Soldier_None:
		break;
	case Soldier_Archer: SoldierName = TEXT("Archer");
		break;
	case Soldier_Footman:SoldierName = TEXT("Footman");
		break;
	case Soldier_Griffin:SoldierName = TEXT("Griffin");
		break;
	case Soldier_Horseman:SoldierName = TEXT("Horseman");
		break;
	case Soldier_Knight:SoldierName = TEXT("Knight");
		break;
	case Soldier_Mage:SoldierName = TEXT("Mage");
		break;
	case Soldier_SiegeEngine:SoldierName = TEXT("SiegeEngine");
		break;
	case Soldier_Peasant:SoldierName = TEXT("Peasant");
		break;
	case Soldier_Num:
		break;
	default:
		break;
	}
	ASoldierPawn * Soldier = nullptr;
	if (!SoldierName.IsEmpty())
	{
		FString DataClassName = FString::Printf(TEXT("%sDataClass"), *SoldierName);
		BaseSoldierDataClass * SoldierData = (BaseSoldierDataClass*)ClassReflectManager::Get()->GetClassByName(TCHAR_TO_UTF8(*DataClassName));
		if (SoldierData)
		{
			SoldierData->SetCommandCenter(this);
			SoldierData->SetSoldierConfigByName(SoldierName);
			SoldierData->SetParentId(GetObjectId());
			SoldiersMap.Add(SoldierData->GetObjectId(), SoldierData);

			Soldier = SoldierData->SpawnSoldierActor(SoldierName);
			if (!Soldier)
			{
				DestroySoldier(SoldierData);
			}
		}
	}
	return Soldier;
}
void CommandCenterDataClass::DestroySoldier(BaseSoldierDataClass * InSoldierData)
{
	SoldiersMap.Remove(InSoldierData->GetObjectId());
	InSoldierData->DestroySoldier();
	delete InSoldierData;
}