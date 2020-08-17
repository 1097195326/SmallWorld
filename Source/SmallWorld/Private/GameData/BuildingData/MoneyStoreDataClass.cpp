
#include "MoneyStoreDataClass.h"
#include "MoneyStoreActor.h"
#include "GameDataManager.h"

G_REGISTER_CLASS(MoneyStoreDataClass)

MoneyStoreDataClass::MoneyStoreDataClass()
{
	BuildingType = B_MoneyStore;
	GoldNum = 0;
}
MoneyStoreDataClass::~MoneyStoreDataClass()
{
    
}
void MoneyStoreDataClass::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("MoneyStoreDataClass");
	BaseBuildingDataClass::Serialization(Writer);

	Writer->WriteValue("GoldNum", GoldNum);

	Writer->WriteObjectEnd();// MoneyStoreDataClass
    
}
void MoneyStoreDataClass::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
	BaseBuildingDataClass::Deserialization(JsonObject->GetObjectField("BaseBuildingDataClass"));

	GoldNum = JsonObject->GetIntegerField("GoldNum");
}
bool MoneyStoreDataClass::SpawnBuildingActor(UWorld * world, const FVector & Location, const FRotator & Rotation)
{
	FTransform SpawnTF(Rotation, Location);
	BuildingActor = world->SpawnActorDeferred<AMoneyStoreActor>(AMoneyStoreActor::StaticClass(), SpawnTF, nullptr, nullptr
		, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	FString MeshName = FString::Printf(TEXT("Mesh%s0"), *BuildingName);
	if (BuildingActor && BuildingActor->SetMeshComponentByIconName(MeshName))
	{
		BuildingActor->SetBuildingData(this);
		BuildingActor->FinishSpawning(SpawnTF);
		return true;
	}
	return false;
}
void  MoneyStoreDataClass::ChangeGoldNum(const int32 & plusNum)
{
	GoldNum += plusNum;
	GoldNum = GoldNum < 0 ? GoldNum = 0 : GoldNum;
	GameDataManager::GetInstance()->GoldDataChangedDelegate.Broadcast();
}