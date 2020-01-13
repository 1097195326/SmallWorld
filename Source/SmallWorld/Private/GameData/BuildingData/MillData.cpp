
#include "MillData.h"

G_REGISTER_CLASS(MillData)

MillData::MillData()
{
	BuildingType = B_Mill;
}
MillData::~MillData()
{
    
}
void MillData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("MillData");
	BaseBuildingData::Serialization(Writer);



	Writer->WriteObjectEnd();// MillData
    
}
void MillData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
    
    
}

