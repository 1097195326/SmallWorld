#include "BlockDataClass.h"
#include "BlockActor.h"


G_REGISTER_CLASS(BlockDataClass)


BlockDataClass::BlockDataClass()
{
	

}
void BlockDataClass::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{


}
void BlockDataClass::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{


}
bool BlockDataClass::SpawnBuildingActor(UWorld * world, const FVector & Location, const FRotator & Rotation)
{
	FTransform SpawnTF(Rotation, Location);
	BuildingActor = world->SpawnActorDeferred<ABlockActor>(ABlockActor::StaticClass(), SpawnTF, nullptr, nullptr
		, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	if (BuildingActor && BuildingActor->SetMeshComponentByIconName(BuildingName))
	{
		BuildingActor->SetBuildingData(this);
		BuildingActor->FinishSpawning(SpawnTF);
		return true;
	}
	return false;
}