
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

ABaseBuildingActor * MillDataClass::SpawnBuildingActor(UWorld * world, const FTransform & SpawnTF, const int32 & InIndex)
{
	FActorSpawnParameters Paramerter;
	Paramerter.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	BuildingActor = world->SpawnActor<AMillActor>(AMillActor::StaticClass(), SpawnTF, Paramerter);
	FString MeshName = FString::Printf(TEXT("Mesh%s%d"), *BuildingName, InIndex);
	if (BuildingActor && BuildingActor->SetMeshComponentByIconName(MeshName))
	{
		BuildingActor->SetBuildingData(this);
	}
	return BuildingActor;
}