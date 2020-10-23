
#include "CommandCenterDataClass.h"
#include "CommandCenterActor.h"


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



	Writer->WriteObjectEnd();// CommandCenterDataClass
    
}
void CommandCenterDataClass::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
    
    
}
ABaseBuildingActor * CommandCenterDataClass::SpawnBuildingActor(UWorld * world, const FTransform & SpawnTF, const int32 && InIndex)
{
	BuildingActor = world->SpawnActorDeferred<ACommandCenterActor>(ACommandCenterActor::StaticClass(), SpawnTF, nullptr, nullptr
		, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	FString MeshName = FString::Printf(TEXT("Mesh%s%d"), *BuildingName, InIndex);
	if (BuildingActor && BuildingActor->SetMeshComponentByIconName(MeshName))
	{
		BuildingActor->SetBuildingData(this);
		BuildingActor->FinishSpawning(SpawnTF);
	}
	return BuildingActor;
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
	return Soldier;
}
void CommandCenterDataClass::DestroySoldier(BaseSoldierDataClass * InSoldierData)
{
	SoldiersMap.Remove(InSoldierData->GetObjectId());
	InSoldierData->DestroySoldier();
	delete InSoldierData;
}