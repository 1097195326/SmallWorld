
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

ABaseBuildingActor * MillDataClass::SpawnBuildingActor(UWorld * world, const FTransform & SpawnTF, const int32 && InIndex)
{
	BuildingActor = world->SpawnActorDeferred<AMillActor>(AMillActor::StaticClass(), SpawnTF, nullptr, nullptr
		, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	FString MeshName = FString::Printf(TEXT("Mesh%s%d"), *BuildingName, InIndex);
	if (BuildingActor && BuildingActor->SetMeshComponentByIconName(MeshName))
	{
		BuildingActor->SetBuildingData(this);
		BuildingActor->FinishSpawning(SpawnTF);
	}
	return BuildingActor;
}