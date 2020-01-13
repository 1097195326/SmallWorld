
#include "GameWorldData.h"


GameWorldData::GameWorldData()
{
    
}
GameWorldData::~GameWorldData()
{
    
}
void GameWorldData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
    
    
}
void GameWorldData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
    
    
}

bool GameWorldData::HordeIdIsValid(FGuid hordeId)
{
	return HordeList.Contains(hordeId);
}

bool GameWorldData::DestroyHordeId(FGuid hordeId)
{
	if (HordeList.Contains(hordeId))
	{
		HordeList.Remove(hordeId);
		return true;
	}
	return false;
}

