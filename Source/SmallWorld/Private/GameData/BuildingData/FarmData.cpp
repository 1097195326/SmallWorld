
#include "FarmData.h"
#include "FarmActor.h"


G_REGISTER_CLASS(FarmData)

FarmData::FarmData()
{
	BuildingType = B_Farm;
	CropNum = 0;
}
FarmData::~FarmData()
{
    
}
void FarmData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("FarmData");
	BaseBuildingData::Serialization(Writer);

	Writer->WriteValue("CropNum", CropNum);

	Writer->WriteObjectEnd();// FarmData
    
}
void FarmData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
	BaseBuildingData::Deserialization(JsonObject->GetObjectField("BaseBuildingData"));
    
	CropNum = JsonObject->GetIntegerField("CropNum");

}
bool FarmData::SpawnBuildingActor(UWorld * world, const FVector & Location, const FRotator & Rotation)
{
	FTransform SpawnTF(Rotation, Location);
	BuildingActor = world->SpawnActorDeferred<AFarmActor>(AFarmActor::StaticClass(), SpawnTF, nullptr, nullptr
		, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	if (BuildingActor && BuildingActor->SetMeshComponentByIconName(BuildingName))
	{
		BuildingActor->SetBuildingData(this);
		BuildingActor->FinishSpawning(SpawnTF);
		return true;
	}
	return false;
}
bool FarmData::IsFull()
{
	return false;
}
