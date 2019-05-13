
#include "MillData.h"


MillData::MillData()
{
    mType = B_Mill;
	mBlockTileType = T_FullDirtTile;
}
MillData::~MillData()
{
    
}
void MillData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
    
    
}
void MillData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
    
    
}

