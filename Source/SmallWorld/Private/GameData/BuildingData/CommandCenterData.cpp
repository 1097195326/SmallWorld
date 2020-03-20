
#include "CommandCenterData.h"
#include "CommandCenterActor.h"


G_REGISTER_CLASS(CommandCenterData)

CommandCenterData::CommandCenterData()
{
	BuildingType = B_CommandCenter;
}
CommandCenterData::~CommandCenterData()
{
    
}
void CommandCenterData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("CommandCenterData");
	BaseBuildingData::Serialization(Writer);



	Writer->WriteObjectEnd();// CommandCenterData
    
}
void CommandCenterData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
    
    
}
bool CommandCenterData::SpawnBuildingActor(UWorld * world, const FVector & Location, const FRotator & Rotation)
{

	return false;
}
