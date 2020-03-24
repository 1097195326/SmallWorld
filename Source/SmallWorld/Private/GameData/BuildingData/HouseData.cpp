#include "HouseData.h"
#include "HouseActor.h"
#include "DataManager.h"


G_REGISTER_CLASS(HouseData)

HouseData::HouseData()
{
	BuildingType = B_House;
	PeopleNum = 0;

}
HouseData::~HouseData()
{
    
}
void HouseData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("HouseData");
	BaseBuildingData::Serialization(Writer);
	
	Writer->WriteValue("PeopleNum", PeopleNum);

	Writer->WriteObjectEnd();// HouseData
    
}
void HouseData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
	BaseBuildingData::Deserialization(JsonObject->GetObjectField("BaseBuildingData"));

	PeopleNum = JsonObject->GetIntegerField("PeopleNum");
    
}
bool HouseData::SpawnBuildingActor(UWorld * world, const FVector & Location, const FRotator & Rotation)
{
	FTransform SpawnTF(Rotation, Location);
	BuildingActor = world->SpawnActorDeferred<AHouseActor>(AHouseActor::StaticClass(), SpawnTF, nullptr, nullptr
		, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	if (BuildingActor && BuildingActor->SetMeshComponentByIconName(BuildingName))
	{
		BuildingActor->SetBuildingData(this);
		BuildingActor->FinishSpawning(SpawnTF);
		return true;
	}
	return false;
}
void HouseData::ChangePeopleNum(int32 plusNum)
{
	PeopleNum += plusNum;
	DataManager::GetInstance()->PeopleDataChangedDelegate.Broadcast();
}
