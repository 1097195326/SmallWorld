
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
ABaseBuildingActor * WallDataClass::SpawnBuildingActor(UWorld * world, const FTransform & SpawnTF, const int32 & InIndex)
{
	FActorSpawnParameters Paramerter;
	Paramerter.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	BuildingActor = world->SpawnActor<AWallActor>(AWallActor::StaticClass(), SpawnTF, Paramerter);
	FString MeshName = FString::Printf(TEXT("Mesh%s%d"), *BuildingName, InIndex);
	if (BuildingActor && BuildingActor->SetMeshComponentByIconName(MeshName))
	{
		BuildingActor->SetBuildingData(this);
	}
	return BuildingActor;
}
