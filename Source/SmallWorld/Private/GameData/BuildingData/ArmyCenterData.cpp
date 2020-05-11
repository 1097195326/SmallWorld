#include "ArmyCenterData.h"
#include "ArmyCenterActor.h"


G_REGISTER_CLASS(ArmyCenterData)

ArmyCenterData::ArmyCenterData()
{
    BuildingType= B_ArmyCenter;
}
ArmyCenterData::~ArmyCenterData()
{
    
}
void ArmyCenterData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("ArmyCenterData");
	BaseBuildingData::Serialization(Writer);


    
	Writer->WriteObjectEnd();// ArmyCenterData
}
void ArmyCenterData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
    
    
}
bool ArmyCenterData::SpawnBuildingActor(UWorld * world, const FVector & Location, const FRotator & Rotation)
{
	FTransform SpawnTF(Rotation, Location);
	BuildingActor = world->SpawnActorDeferred<AArmyCenterActor>(AArmyCenterActor::StaticClass(), SpawnTF,nullptr,nullptr
	,ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	if (BuildingActor && BuildingActor->SetMeshComponentByIconName(BuildingName))
	{
		BuildingActor->SetBuildingData(this);
		BuildingActor->FinishSpawning(SpawnTF);
		return true;
	}
	return false;
}
void ArmyCenterData::TrainSoldier(ESoldierType InSoldierType, int32 InNum)
{
	FString  TemTrainKey = FString::Printf(TEXT("%s_%d"),*GetID().ToString(),InSoldierType);
	switch (InSoldierType)
	{
	case S_None:
		break;
	case S_Archer:
		ProgressManager::GetInstance()->RegisterProgress(TCHAR_TO_UTF8(*TemTrainKey), InNum, 1, 0, 100, this, &ArmyCenterData::OnTrainArcherCallback);
		break;
	case S_Footman:
		ProgressManager::GetInstance()->RegisterProgress(TCHAR_TO_UTF8(*TemTrainKey), InNum, 1, 0, 100, this, &ArmyCenterData::OnTrainFootmanCallback);
		break;
	case S_Griffin:
		break;
	case S_Horseman:
		break;
	case S_Knight:
		break;
	case S_Mage:
		break;
	case S_SiegeEngine:
		break;
	case S_Peasant:
		break;
	default:
		break;
	}
}
void ArmyCenterData::OnTrainArcherCallback(float InProgress, bool InIsFinish, int LoopTimes)
{

	BuildingActor->RefreshView();
}
void ArmyCenterData::OnTrainFootmanCallback(float InProgress, bool InIsFinish, int LoopTimes)
{

	BuildingActor->RefreshView();
}