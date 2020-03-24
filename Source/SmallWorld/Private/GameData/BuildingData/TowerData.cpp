
#include "TowerData.h"
#include "TowerActor.h"

G_REGISTER_CLASS(TowerData)

TowerData::TowerData()
{
	BuildingType = B_Tower;
    
}
TowerData::~TowerData()
{
    
}
void TowerData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("TowerData");
	BaseBuildingData::Serialization(Writer);



	Writer->WriteObjectEnd();// TowerData
    
}
void TowerData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
    
    
}
bool TowerData::SpawnBuildingActor(UWorld * world, const FVector & Location, const FRotator & Rotation)
{
	FTransform SpawnTF(Rotation, Location);
	BuildingActor = world->SpawnActorDeferred<ATowerActor>(ATowerActor::StaticClass(), SpawnTF, nullptr, nullptr
		, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	if (BuildingActor && BuildingActor->SetMeshComponentByIconName(BuildingName))
	{
		BuildingActor->SetBuildingData(this);
		BuildingActor->FinishSpawning(SpawnTF);
		return true;
	}
	return false;
}

