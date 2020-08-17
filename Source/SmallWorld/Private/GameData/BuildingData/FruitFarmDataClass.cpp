#include "FruitFarmDataClass.h"
#include "FruitFarmActor.h"

G_REGISTER_CLASS(FruitFarmDataClass)


FruitFarmDataClass::FruitFarmDataClass()
{
	BuildingType = B_FruitFarm;
	FruitNum = 0;
}
FruitFarmDataClass::~FruitFarmDataClass()
{

}
void FruitFarmDataClass::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("FruitFarmDataClass");
	BaseBuildingDataClass::Serialization(Writer);

	Writer->WriteValue("FruitNum", FruitNum);

	Writer->WriteObjectEnd();// FruitFarmDataClass

}
void FruitFarmDataClass::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
	BaseBuildingDataClass::Deserialization(JsonObject->GetObjectField("BaseBuildingDataClass"));

	FruitNum = JsonObject->GetIntegerField("FruitNum");


}
bool FruitFarmDataClass::SpawnBuildingActor(UWorld * world, const FTransform & SpawnTF, const int32 && InIndex)
{
	BuildingActor = world->SpawnActorDeferred<AFruitFarmActor>(AFruitFarmActor::StaticClass(), SpawnTF, nullptr, nullptr
		, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	FString MeshName = FString::Printf(TEXT("Mesh%s%d"), *BuildingName, InIndex);
	if (BuildingActor && BuildingActor->SetMeshComponentByIconName(MeshName))
	{
		BuildingActor->SetBuildingData(this);
		BuildingActor->FinishSpawning(SpawnTF);
		return true;
	}
	return false;
}
bool FruitFarmDataClass::IsFull()
{
	return false;
}