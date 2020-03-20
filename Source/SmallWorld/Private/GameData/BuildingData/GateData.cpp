
#include "GateData.h"
#include "GateActor.h"

G_REGISTER_CLASS(GateData)

GateData::GateData()
{
	BuildingType = B_Gate;
    
    
}
GateData::~GateData()
{
    
}
void GateData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("GateData");
	BaseBuildingData::Serialization(Writer);



	Writer->WriteObjectEnd();// GateData
    
}
void GateData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
    
    
}
bool GateData::SpawnBuildingActor(UWorld * world, const FVector & Location, const FRotator & Rotation)
{

	return false;
}

