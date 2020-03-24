
#include "MillData.h"
#include "MillActor.h"

G_REGISTER_CLASS(MillData)

MillData::MillData()
{
	BuildingType = B_Mill;
	//MillData * __restrict testPtr;

}
MillData::~MillData()
{
    
}
void MillData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("MillData");
	BaseBuildingData::Serialization(Writer);



	Writer->WriteObjectEnd();// MillData
    
}
void MillData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
    
    
}

bool MillData::SpawnBuildingActor(UWorld * world, const FVector & Location, const FRotator & Rotation)
{
	FTransform SpawnTF(Rotation, Location);
	BuildingActor = world->SpawnActorDeferred<AMillActor>(AMillActor::StaticClass(), SpawnTF, nullptr, nullptr
		, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	if (BuildingActor && BuildingActor->SetMeshComponentByIconName(BuildingName))
	{
		BuildingActor->SetBuildingData(this);
		BuildingActor->FinishSpawning(SpawnTF);
		return true;
	}
	return false;
}