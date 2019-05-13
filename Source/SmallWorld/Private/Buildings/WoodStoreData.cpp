
#include "WoodStoreData.h"


WoodStoreData::WoodStoreData()
{
    mType = B_WoodStore;
	mBlockTileType = T_FullDirtTile;
}
WoodStoreData::~WoodStoreData()
{
    
}
void WoodStoreData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
    
    
}
void WoodStoreData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
    
    
}

