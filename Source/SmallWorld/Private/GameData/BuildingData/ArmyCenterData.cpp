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

	//Writer->WriteArrayStart("HaveSoldiers");
	//for (auto TemSol : HaveSoldiers)
	//{
	//	Writer->WriteObjectStart();
	//	Writer->WriteValue("Key", TemSol.Key);
	//	Writer->WriteValue("Value", TemSol.Value);
	//	Writer->WriteObjectEnd();
	//}
	//Writer->WriteArrayEnd(); //HaveSoldiers

	//Writer->WriteArrayStart("TrainSoldiers");
	//for (auto TemSol : TrainSoldiers)
	//{
	//	Writer->WriteObjectStart();
	//	Writer->WriteValue("Key", TemSol.Key);
	//	Writer->WriteValue("Value", TemSol.Value);
	//	Writer->WriteObjectEnd();
	//}
	//Writer->WriteArrayEnd(); //TrainSoldiers
    
	Writer->WriteObjectEnd();// ArmyCenterData
}
void ArmyCenterData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
	BaseBuildingData::Deserialization(JsonObject->GetObjectField("BaseBuildingData"));

	/*TArray<TSharedPtr<FJsonValue>>  JHaveSoldiers=JsonObject->GetArrayField("HaveSoldiers");
    for (auto jValue : JHaveSoldiers)
    {
		ESoldierType ekey = (ESoldierType)jValue->AsObject()->GetIntegerField("Key");
		int32 ivalue = jValue->AsObject()->GetIntegerField("Value");
		HaveSoldiers.Add(ekey, ivalue);
    }
	TArray<TSharedPtr<FJsonValue>>  JTrainSoldiers = JsonObject->GetArrayField("TrainSoldiers");
	for (auto jValue : JTrainSoldiers)
	{
		ESoldierType ekey = (ESoldierType)jValue->AsObject()->GetIntegerField("Key");
		int32 ivalue = jValue->AsObject()->GetIntegerField("Value");
		TrainSoldiers.Add(ekey, ivalue);
	}*/
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
void ArmyCenterData::OnTrainArcherCallback(const float & InProgress, const bool & InIsFinish, const int & LoopTimes)
{
	OnTrainCallback(SoldierStorageMap[S_Archer], SoldierTrainMap[S_Archer], InProgress, InIsFinish, LoopTimes);
}
void ArmyCenterData::OnTrainFootmanCallback(const float & InProgress, const bool & InIsFinish, const int & LoopTimes)
{
	OnTrainCallback(SoldierStorageMap[S_Footman], SoldierTrainMap[S_Footman],InProgress,InIsFinish, LoopTimes);
}
void ArmyCenterData::OnTrainCallback(SoldierStorageState & StorageState, SoldierTrainState & TrainState, const float & InProgress, const bool & InIsFinish, const int & LoopTimes)
{
	TrainState.CurrentTrainProgress = InProgress;
	TrainState.OneLoopIsFinish = InIsFinish;
	TrainState.RemainLoopTimes = LoopTimes;
	if (InIsFinish)
	{
		StorageState.HaveNum += 1;
	}
	BuildingActor->RefreshView();
}