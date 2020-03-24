
#include "MoneyStoreData.h"
#include "MoneyStoreActor.h"
#include "DataManager.h"

G_REGISTER_CLASS(MoneyStoreData)

MoneyStoreData::MoneyStoreData()
{
	BuildingType = B_MoneyStore;
	GoldNum = 0;
}
MoneyStoreData::~MoneyStoreData()
{
    
}
void MoneyStoreData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("MoneyStoreData");
	BaseBuildingData::Serialization(Writer);

	Writer->WriteValue("GoldNum", GoldNum);

	Writer->WriteObjectEnd();// MoneyStoreData
    
}
void MoneyStoreData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
	BaseBuildingData::Deserialization(JsonObject->GetObjectField("BaseBuildingData"));

	GoldNum = JsonObject->GetIntegerField("GoldNum");
}
bool MoneyStoreData::SpawnBuildingActor(UWorld * world, const FVector & Location, const FRotator & Rotation)
{
	FTransform SpawnTF(Rotation, Location);
	BuildingActor = world->SpawnActorDeferred<AMoneyStoreActor>(AMoneyStoreActor::StaticClass(), SpawnTF, nullptr, nullptr
		, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	if (BuildingActor && BuildingActor->SetMeshComponentByIconName(BuildingName))
	{
		BuildingActor->SetBuildingData(this);
		BuildingActor->FinishSpawning(SpawnTF);
		return true;
	}
	return false;
}
void  MoneyStoreData::ChangeGoldNum(const int32 & plusNum)
{
	GoldNum += plusNum;
	GoldNum = GoldNum < 0 ? GoldNum = 0 : GoldNum;
	DataManager::GetInstance()->GoldDataChangedDelegate.Broadcast();
}