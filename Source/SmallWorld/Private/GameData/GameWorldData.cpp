
#include "GameWorldData.h"
#include "UserData.h"

GameWorldData::GameWorldData()
{
    
}
GameWorldData::~GameWorldData()
{
    for (auto hordeData : HordeDataMap)
    {
		delete hordeData.Value;
    }
	HordeDataMap.Empty();
}
void GameWorldData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("GameWorldData");

		Writer->WriteObjectStart("HordeDataMap");
		for (auto temHordeData : HordeDataMap)
		{
			temHordeData.Value->Serialization(Writer);
		}
		Writer->WriteObjectEnd();//HordeDataMap
	Writer->WriteObjectEnd();//GameWorldData
}
void GameWorldData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
	TSharedPtr<FJsonObject> JHordeDataMap = JsonObject->GetObjectField("HordeDataMap");
	for (auto jPair : JHordeDataMap->Values)
	{
		FString DataClass = jPair.Key;
		HordeData * Data = (HordeData*)(ReflectManager::Get()->GetClassByName(TCHAR_TO_UTF8(*DataClass)));
		if (Data)
		{
			Data->Deserialization(jPair.Value->AsObject());
			HordeDataMap.Add(Data->GetID(), Data);
		}
	}
    
}
void GameWorldData::InitWorldData()
{
	if (HordeDataMap.Num() == 0)
	{
		HordeData * TemHordeData = CreateHordeData();

	}
}
void GameWorldData::InitUserData(UserData * userData)
{
	HordeData * userHordeData = nullptr;
	if (HordeIdIsValid(userData->GetHordeId()))
	{
		userHordeData = HordeDataMap[userData->GetHordeId()];
	}
	else
	{
		userHordeData = CreateHordeData();
		userData->hordeId = userHordeData->GetID();
	}
	userData->hordeData = userHordeData;
}
HordeData * GameWorldData::CreateHordeData()
{
	HordeData * resData = new HordeData();
	HordeDataMap.Add(resData->GetID(), resData);
	return resData;
}
HordeData * GameWorldData::GetHordeDataById(FGuid hordeId)
{
	return HordeDataMap[hordeId];
}
bool GameWorldData::HordeIdIsValid(FGuid hordeId)
{
	return hordeId.IsValid() && HordeDataMap.Contains(hordeId);
}
bool GameWorldData::DestroyHordeId(FGuid hordeId)
{
	if (HordeDataMap.Contains(hordeId))
	{
		delete HordeDataMap[hordeId];
		HordeDataMap.Remove(hordeId);
		return true;
	}
	return false;
}

