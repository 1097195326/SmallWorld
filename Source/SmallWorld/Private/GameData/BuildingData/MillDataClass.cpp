
#include "MillDataClass.h"
#include "MillActor.h"

G_REGISTER_CLASS(MillDataClass)

MillDataClass::MillDataClass()
{
	BuildingType = B_Mill;
	//MillDataClass * __restrict testPtr;

}
MillDataClass::~MillDataClass()
{
    
}
void MillDataClass::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("MillDataClass");
	BaseBuildingDataClass::Serialization(Writer);



	Writer->WriteObjectEnd();// MillDataClass
    
}
void MillDataClass::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
    
    
}

bool MillDataClass::SpawnBuildingActor(UWorld * world, const FVector & Location, const FRotator & Rotation)
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