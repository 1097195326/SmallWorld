
#include "TowerData.h"
#include "TowerActor.h"

G_REGISTER_CLASS(TowerData)

TowerData::TowerData()
{
	BuildingType = B_Tower;
    
}
TowerData::~TowerData()
{
    
}
void TowerData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("TowerData");
	BaseBuildingData::Serialization(Writer);



	Writer->WriteObjectEnd();// TowerData
    
}
void TowerData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
    
    
}
bool TowerData::SpawnBuildingActor(UWorld * world, const FVector & Location, const FRotator & Rotation)
{

	return false;
}

