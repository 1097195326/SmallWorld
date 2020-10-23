
#include "BakeryDataClass.h"
#include "BakeryActor.h"


G_REGISTER_CLASS(BakeryDataClass)

BakeryDataClass::BakeryDataClass()
{
    BuildingType = B_Bakery;

}
BakeryDataClass::~BakeryDataClass()
{
    
}
void BakeryDataClass::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("BakeryDataClass");
	BaseBuildingDataClass::Serialization(Writer);



	Writer->WriteObjectEnd();// BakeryDataClass
    
}
void BakeryDataClass::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
    
    
}
ABaseBuildingActor * BakeryDataClass::SpawnBuildingActor(UWorld * world, const FTransform & SpawnTF, const int32 && InIndex)
{
	BuildingActor = world->SpawnActorDeferred<ABakeryActor>(ABakeryActor::StaticClass(), SpawnTF, nullptr, nullptr
		, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	FString MeshName = FString::Printf(TEXT("Mesh%s%d"), *BuildingName, InIndex);
	if (BuildingActor && BuildingActor->SetMeshComponentByIconName(MeshName))
	{
		BuildingActor->SetBuildingData(this);
		BuildingActor->FinishSpawning(SpawnTF);
	}
	return BuildingActor;
}
