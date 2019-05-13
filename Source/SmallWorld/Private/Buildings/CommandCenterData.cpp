
#include "CommandCenterData.h"


CommandCenterData::CommandCenterData()
{
    mType = B_CommandCenter;
	mBlockTileType = T_CenterDirtTile;
}
CommandCenterData::~CommandCenterData()
{
    
}
void CommandCenterData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
    
    
}
void CommandCenterData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
    
    
}

