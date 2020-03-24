
#include "GateData.h"
#include "GateActor.h"

G_REGISTER_CLASS(GateData)

GateData::GateData()
{
	BuildingType = B_Gate;
    
    
}
GateData::~GateData()
{
    
}
void GateData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("GateData");
	BaseBuildingData::Serialization(Writer);



	Writer->WriteObjectEnd();// GateData
    
}
void GateData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
    
    
}
bool GateData::SpawnBuildingActor(UWorld * world, const FVector & Location, const FRotator & Rotation)
{
	FTransform SpawnTF(Rotation, Location);
	BuildingActor = world->SpawnActorDeferred<AGateActor>(AGateActor::StaticClass(), SpawnTF, nullptr, nullptr
		, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	if (BuildingActor && BuildingActor->SetMeshComponentByIconName(BuildingName))
	{
		BuildingActor->SetBuildingData(this);
		BuildingActor->FinishSpawning(SpawnTF);
		return true;
	}
	return false;
}

