
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
bool BakeryDataClass::SpawnBuildingActor(UWorld * world, const FVector & Location, const FRotator & Rotation)
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
