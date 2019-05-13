
#include "BakeryData.h"


BakeryData::BakeryData()
{
    mType = B_Bakery;
	mBlockTileType = T_FullDirtTile;

}
BakeryData::~BakeryData()
{
    
}
void BakeryData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
    
    
}
void BakeryData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
    
    
}

