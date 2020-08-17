
#include "TowerDataClass.h"
#include "TowerActor.h"

G_REGISTER_CLASS(TowerDataClass)

TowerDataClass::TowerDataClass()
{
	BuildingType = B_Tower;
    
}
TowerDataClass::~TowerDataClass()
{
    
}
void TowerDataClass::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("TowerDataClass");
	BaseBuildingDataClass::Serialization(Writer);



	Writer->WriteObjectEnd();// TowerDataClass
    
}
void TowerDataClass::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
    
    
}
bool TowerDataClass::SpawnBuildingActor(UWorld * world, const FTransform & SpawnTF, const int32 && InIndex)
{
	BuildingActor = world->SpawnActorDeferred<ATowerActor>(ATowerActor::StaticClass(), SpawnTF, nullptr, nullptr
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

