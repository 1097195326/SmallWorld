#include "ArmyCenterData.h"



ArmyCenterData::ArmyCenterData()
{
    mType= B_ArmyCenter;
	mBlockTileType = T_CenterDirtTile;
}
ArmyCenterData::~ArmyCenterData()
{
    
}
void ArmyCenterData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
    
    
}
void ArmyCenterData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
    
    
}
