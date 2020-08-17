
#include "FarmDataClass.h"
#include "FarmActor.h"


G_REGISTER_CLASS(FarmDataClass)

FarmDataClass::FarmDataClass()
{
	BuildingType = B_Farm;
	CropNum = 0;
}
FarmDataClass::~FarmDataClass()
{
    
}
void FarmDataClass::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("FarmDataClass");
	BaseBuildingDataClass::Serialization(Writer);

	Writer->WriteValue("CropNum", CropNum);

	Writer->WriteObjectEnd();// FarmDataClass
    
}
void FarmDataClass::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
	BaseBuildingDataClass::Deserialization(JsonObject->GetObjectField("BaseBuildingDataClass"));
    
	CropNum = JsonObject->GetIntegerField("CropNum");

}
bool FarmDataClass::SpawnBuildingActor(UWorld * world, const FVector & Location, const FRotator & Rotation)
{
	FTransform SpawnTF(Rotation, Location);
	BuildingActor = world->SpawnActorDeferred<AFarmActor>(AFarmActor::StaticClass(), SpawnTF, nullptr, nullptr
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
bool FarmDataClass::IsFull()
{
	return false;
}
