
#include "BakeryData.h"
#include "BakeryActor.h"


G_REGISTER_CLASS(BakeryData)

BakeryData::BakeryData()
{
    BuildingType = B_Bakery;

}
BakeryData::~BakeryData()
{
    
}
void BakeryData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("BakeryData");
	BaseBuildingData::Serialization(Writer);



	Writer->WriteObjectEnd();// BakeryData
    
}
void BakeryData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
    
    
}
bool BakeryData::SpawnBuildingActor(UWorld * world, const FVector & Location, const FRotator & Rotation)
{
	FTransform SpawnTF(Rotation, Location);
	BuildingActor = world->SpawnActorDeferred<ABakeryActor>(ABakeryActor::StaticClass(), SpawnTF, nullptr, nullptr
		, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	if (BuildingActor && BuildingActor->SetMeshComponentByIconName(BuildingName))
	{
		BuildingActor->SetBuildingData(this);
		BuildingActor->FinishSpawning(SpawnTF);
		return true;
	}
	return false;
}
