
#include "FarmData.h"


FarmData::FarmData()
{
    mType = B_Farm;
	mBlockTileType = T_CenterDirtTile;
}
FarmData::~FarmData()
{
    
}
void FarmData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
    
    
}
void FarmData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
    
    
}

