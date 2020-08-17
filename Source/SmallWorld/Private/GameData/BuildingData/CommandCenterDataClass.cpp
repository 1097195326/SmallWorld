
#include "CommandCenterDataClass.h"
#include "CommandCenterActor.h"


G_REGISTER_CLASS(CommandCenterDataClass)

CommandCenterDataClass::CommandCenterDataClass()
{
	BuildingType = B_CommandCenter;
}
CommandCenterDataClass::~CommandCenterDataClass()
{
    
}
void CommandCenterDataClass::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("CommandCenterDataClass");
	BaseBuildingDataClass::Serialization(Writer);



	Writer->WriteObjectEnd();// CommandCenterDataClass
    
}
void CommandCenterDataClass::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
    
    
}
bool CommandCenterDataClass::SpawnBuildingActor(UWorld * world, const FTransform & SpawnTF, const int32 && InIndex)
{
	BuildingActor = world->SpawnActorDeferred<ACommandCenterActor>(ACommandCenterActor::StaticClass(), SpawnTF, nullptr, nullptr
		, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	FString MeshName = FString::Printf(TEXT("Mesh%s%d"), *BuildingName, InIndex);
	if (BuildingActor && BuildingActor->SetMeshComponentByIconName(MeshName))
	{
		BuildingActor->SetBuildingData(this);
		BuildingActor->FinishSpawning(SpawnTF);
		return true;
	}
	return false;
}
