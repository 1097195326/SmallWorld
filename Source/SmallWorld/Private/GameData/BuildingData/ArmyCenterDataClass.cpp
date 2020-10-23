#include "ArmyCenterDataClass.h"
#include "ArmyCenterActor.h"


G_REGISTER_CLASS(ArmyCenterDataClass)

ArmyCenterDataClass::ArmyCenterDataClass()
{
    BuildingType= B_ArmyCenter;
}
ArmyCenterDataClass::~ArmyCenterDataClass()
{
    
}
void ArmyCenterDataClass::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("ArmyCenterDataClass");
	BaseBuildingDataClass::Serialization(Writer);

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
    
	Writer->WriteObjectEnd();// ArmyCenterDataClass
}
void ArmyCenterDataClass::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
	BaseBuildingDataClass::Deserialization(JsonObject->GetObjectField("BaseBuildingDataClass"));

	/*TArray<TSharedPtr<FJsonValue>>  JHaveSoldiers=JsonObject->GetArrayField("HaveSoldiers");
    for (auto jValue : JHaveSoldiers)
    {
		SoldierTypeEnum ekey = (SoldierTypeEnum)jValue->AsObject()->GetIntegerField("Key");
		int32 ivalue = jValue->AsObject()->GetIntegerField("Value");
		HaveSoldiers.Add(ekey, ivalue);
    }
	TArray<TSharedPtr<FJsonValue>>  JTrainSoldiers = JsonObject->GetArrayField("TrainSoldiers");
	for (auto jValue : JTrainSoldiers)
	{
		SoldierTypeEnum ekey = (SoldierTypeEnum)jValue->AsObject()->GetIntegerField("Key");
		int32 ivalue = jValue->AsObject()->GetIntegerField("Value");
		TrainSoldiers.Add(ekey, ivalue);
	}*/
}
ABaseBuildingActor * ArmyCenterDataClass::SpawnBuildingActor(UWorld * world, const FTransform & SpawnTF, const int32 && InIndex)
{
	BuildingActor = world->SpawnActorDeferred<AArmyCenterActor>(AArmyCenterActor::StaticClass(), SpawnTF,nullptr,nullptr
	,ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	FString MeshName = FString::Printf(TEXT("Mesh%s%d"), *BuildingName,InIndex);
	if (BuildingActor && BuildingActor->SetMeshComponentByIconName(MeshName))
	{
		BuildingActor->SetBuildingData(this);
		BuildingActor->FinishSpawning(SpawnTF);
	}
	return BuildingActor;
}
void ArmyCenterDataClass::TrainSoldier(SoldierTypeEnum InSoldierType, int32 InNum)
{
	FString  TemTrainKey = FString::Printf(TEXT("%s_%d"),*GetObjectId().ToString(),InSoldierType);
	switch (InSoldierType)
	{
	case Soldier_None:
		break;
	case Soldier_Archer:
		ProgressManager::GetInstance()->RegisterProgress(TCHAR_TO_UTF8(*TemTrainKey), InNum, 1, 0, 100, this, &ArmyCenterDataClass::OnTrainArcherCallback);
		break;
	case Soldier_Footman:
		ProgressManager::GetInstance()->RegisterProgress(TCHAR_TO_UTF8(*TemTrainKey), InNum, 1, 0, 100, this, &ArmyCenterDataClass::OnTrainFootmanCallback);
		break;
	case Soldier_Griffin:
		break;
	case Soldier_Horseman:
		break;
	case Soldier_Knight:
		break;
	case Soldier_Mage:
		break;
	case Soldier_SiegeEngine:
		break;
	case Soldier_Peasant:
		break;
	default:
		break;
	}
}
void ArmyCenterDataClass::OnTrainArcherCallback(const float & InProgress, const bool & InIsFinish, const int & LoopTimes)
{
	OnTrainCallback(SoldierStorageMap[Soldier_Archer], SoldierTrainMap[Soldier_Archer], InProgress, InIsFinish, LoopTimes);
}
void ArmyCenterDataClass::OnTrainFootmanCallback(const float & InProgress, const bool & InIsFinish, const int & LoopTimes)
{
	OnTrainCallback(SoldierStorageMap[Soldier_Footman], SoldierTrainMap[Soldier_Footman],InProgress,InIsFinish, LoopTimes);
}
void ArmyCenterDataClass::OnTrainCallback(SoldierStorageState & StorageState, SoldierTrainState & TrainState, const float & InProgress, const bool & InIsFinish, const int & LoopTimes)
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