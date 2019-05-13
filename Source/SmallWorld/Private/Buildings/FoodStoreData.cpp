
#include "FoodStoreData.h"


FoodStoreData::FoodStoreData()
{
    mType = B_FoodStore;
	mBlockTileType = T_CenterDirtTile;
}
FoodStoreData::~FoodStoreData()
{
    
}
void FoodStoreData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
    
    
}
void FoodStoreData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
    
    
}

