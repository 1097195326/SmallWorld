
#include "StoneStoreData.h"


StoneStoreData::StoneStoreData()
{
    mType = B_StoneStore;
	mBlockTileType = T_FullDirtTile;
}
StoneStoreData::~StoneStoreData()
{
    
}
void StoneStoreData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
    
    
}
void StoneStoreData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
    
    
}

