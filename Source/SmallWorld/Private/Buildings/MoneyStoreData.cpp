
#include "MoneyStoreData.h"


MoneyStoreData::MoneyStoreData()
{
    mType = B_MoneyStore;
	mBlockTileType = T_FullDirtTile;
}
MoneyStoreData::~MoneyStoreData()
{
    
}
void MoneyStoreData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
    
    
}
void MoneyStoreData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
    
    
}

