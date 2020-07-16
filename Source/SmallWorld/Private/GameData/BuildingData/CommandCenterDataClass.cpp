
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
bool CommandCenterDataClass::SpawnBuildingActor(UWorld * world, const FVector & Location, const FRotator & Rotation)
{
	FTransform SpawnTF(Rotation, Location);
	BuildingActor = world->SpawnActorDeferred<ACommandCenterActor>(ACommandCenterActor::StaticClass(), SpawnTF, nullptr, nullptr
		, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	if (BuildingActor && BuildingActor->SetMeshComponentByIconName(BuildingName))
	{
		BuildingActor->SetBuildingData(this);
		BuildingActor->FinishSpawning(SpawnTF);
		return true;
	}
	return false;
}
