
#include "BakeryData.h"

G_REGISTER_CLASS(BakeryData)

BakeryData::BakeryData()
{
    BuildingType = B_Bakery;

}
BakeryData::~BakeryData()
{
    
}
void BakeryData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("BakeryData");
	BaseBuildingData::Serialization(Writer);



	Writer->WriteObjectEnd();// BakeryData
    
}
void BakeryData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
    
    
}

