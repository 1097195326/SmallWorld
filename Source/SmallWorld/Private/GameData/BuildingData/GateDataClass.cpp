
#include "GateDataClass.h"
#include "GateActor.h"

G_REGISTER_CLASS(GateDataClass)

GateDataClass::GateDataClass()
{
	BuildingType = B_Gate;
    
    
}
GateDataClass::~GateDataClass()
{
    
}
void GateDataClass::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("GateDataClass");
	BaseBuildingDataClass::Serialization(Writer);



	Writer->WriteObjectEnd();// GateDataClass
    
}
void GateDataClass::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
    
    
}
bool GateDataClass::SpawnBuildingActor(UWorld * world, const FVector & Location, const FRotator & Rotation)
{
	FTransform SpawnTF(Rotation, Location);
	BuildingActor = world->SpawnActorDeferred<AGateActor>(AGateActor::StaticClass(), SpawnTF, nullptr, nullptr
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

