
#include "FarmData.h"

G_REGISTER_CLASS(FarmData)

FarmData::FarmData()
{
	BuildingType = B_Farm;
}
FarmData::~FarmData()
{
    
}
void FarmData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("FarmData");
	BaseBuildingData::Serialization(Writer);



	Writer->WriteObjectEnd();// FarmData
    
}
void FarmData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
    
    
}

