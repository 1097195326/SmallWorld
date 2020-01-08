
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
int32 GameWorldData::CreateHordeId()
{
	int32 HordeId = 1;
	while (HordeList.Contains(HordeId))
	{
		++HordeId;
	}
	HordeList.AddUnique(HordeId);
	
	return HordeId;
}

bool GameWorldData::HordeIdIsValid(int32 hordeId)
{
	return HordeList.Contains(hordeId);
}

bool GameWorldData::DestroyHordeId(int32 hordeId)
{
	if (HordeList.Contains(hordeId))
	{
		HordeList.Remove(hordeId);
		return true;
	}
	return false;
}

