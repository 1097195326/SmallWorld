
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
ABaseBuildingActor * FarmDataClass::SpawnBuildingActor(UWorld * world, const FTransform & SpawnTF, const int32 & InIndex)
{
	FActorSpawnParameters Paramerter;
	Paramerter.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	BuildingActor = world->SpawnActor<AFarmActor>(AFarmActor::StaticClass(), SpawnTF, Paramerter);
	FString MeshName = FString::Printf(TEXT("Mesh%s%d"), *BuildingName, InIndex);
	if (BuildingActor && BuildingActor->SetMeshComponentByIconName(MeshName))
	{
		BuildingActor->SetBuildingData(this);
	}
	return BuildingActor;
}
bool FarmDataClass::IsFull()
{
	return false;
}
