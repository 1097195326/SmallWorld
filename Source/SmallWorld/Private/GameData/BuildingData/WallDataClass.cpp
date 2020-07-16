
#include "WallDataClass.h"
#include "WallActor.h"

G_REGISTER_CLASS(WallDataClass)

WallDataClass::WallDataClass()
{
	BuildingType = B_Wall;
    
}
WallDataClass::~WallDataClass()
{
    
}
void WallDataClass::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("WallDataClass");
	BaseBuildingDataClass::Serialization(Writer);



	Writer->WriteObjectEnd();// WallDataClass
    
}
void WallDataClass::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
    
    
}
bool WallDataClass::SpawnBuildingActor(UWorld * world, const FVector & Location, const FRotator & Rotation)
{
	FTransform SpawnTF(Rotation, Location);
	BuildingActor = world->SpawnActorDeferred<AWallActor>(AWallActor::StaticClass(), SpawnTF, nullptr, nullptr
		, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	if (BuildingActor && BuildingActor->SetMeshComponentByIconName(BuildingName))
	{
		BuildingActor->SetBuildingData(this);
		BuildingActor->FinishSpawning(SpawnTF);
		return true;
	}
	return false;
}
