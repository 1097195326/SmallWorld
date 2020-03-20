#include "ArmyCenterData.h"
#include "ArmyCenterActor.h"

G_REGISTER_CLASS(ArmyCenterData)

ArmyCenterData::ArmyCenterData()
{
    BuildingType= B_ArmyCenter;
}
ArmyCenterData::~ArmyCenterData()
{
    
}
void ArmyCenterData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("ArmyCenterData");
	BaseBuildingData::Serialization(Writer);


    
	Writer->WriteObjectEnd();// ArmyCenterData
}
void ArmyCenterData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
    
    
}
bool ArmyCenterData::SpawnBuildingActor(UWorld * world, const FVector & Location, const FRotator & Rotation)
{
	FTransform SpawnTF(Rotation, Location);
	BuildingActor = world->SpawnActorDeferred<AArmyCenterActor>(AArmyCenterActor::StaticClass(), SpawnTF,nullptr,nullptr
	,ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	if (BuildingActor)
	{
		BuildingActor->SetBuildingData(this);
		BuildingActor->SetMeshComponent(BuildingName);
		BuildingActor->FinishSpawning(SpawnTF);
		return true;
	}
	return false;
}