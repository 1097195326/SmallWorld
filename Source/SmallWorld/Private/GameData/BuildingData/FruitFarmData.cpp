#include "FruitFarmData.h"
#include "FruitFarmActor.h"

G_REGISTER_CLASS(FruitFarmData)


FruitFarmData::FruitFarmData()
{
	BuildingType = B_FruitFarm;
	FruitNum = 0;
}
FruitFarmData::~FruitFarmData()
{

}
void FruitFarmData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("FruitFarmData");
	BaseBuildingData::Serialization(Writer);

	Writer->WriteValue("FruitNum", FruitNum);

	Writer->WriteObjectEnd();// FruitFarmData

}
void FruitFarmData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
	BaseBuildingData::Deserialization(JsonObject->GetObjectField("BaseBuildingData"));

	FruitNum = JsonObject->GetIntegerField("FruitNum");


}
bool FruitFarmData::SpawnBuildingActor(UWorld * world, const FVector & Location, const FRotator & Rotation)
{
	FTransform SpawnTF(Rotation, Location);
	BuildingActor = world->SpawnActorDeferred<AFruitFarmActor>(AFruitFarmActor::StaticClass(), SpawnTF, nullptr, nullptr
		, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	if (BuildingActor && BuildingActor->SetMeshComponentByIconName(BuildingName))
	{
		BuildingActor->SetBuildingData(this);
		BuildingActor->FinishSpawning(SpawnTF);
		return true;
	}
	return false;
}
bool FruitFarmData::IsFull()
{
	return false;
}