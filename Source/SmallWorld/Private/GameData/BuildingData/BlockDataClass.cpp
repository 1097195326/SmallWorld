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
ABaseBuildingActor * BlockDataClass::SpawnBuildingActor(UWorld * world, const FTransform & SpawnTF, const int32 && InIndex)
{
	BuildingActor = world->SpawnActorDeferred<ABlockActor>(ABlockActor::StaticClass(), SpawnTF, nullptr, nullptr
		, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	FString MeshName = FString::Printf(TEXT("Mesh%s%d"), *BuildingName, InIndex);
	if (BuildingActor && BuildingActor->SetMeshComponentByIconName(MeshName))
	{
		BuildingActor->SetBuildingData(this);
		BuildingActor->FinishSpawning(SpawnTF);
	}
	return BuildingActor;
}