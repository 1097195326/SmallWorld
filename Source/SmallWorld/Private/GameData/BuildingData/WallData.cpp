
#include "WallData.h"
#include "WallActor.h"

G_REGISTER_CLASS(WallData)

WallData::WallData()
{
	BuildingType = B_Wall;
    
}
WallData::~WallData()
{
    
}
void WallData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("WallData");
	BaseBuildingData::Serialization(Writer);



	Writer->WriteObjectEnd();// WallData
    
}
void WallData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
    
    
}
bool WallData::SpawnBuildingActor(UWorld * world, const FVector & Location, const FRotator & Rotation)
{

	return false;
}
