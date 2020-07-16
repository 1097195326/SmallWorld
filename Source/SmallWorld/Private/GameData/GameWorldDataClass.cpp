
#include "GameWorldDataClass.h"
#include "UserDataClass.h"

GameWorldDataClass::GameWorldDataClass()
{
    
}
GameWorldDataClass::~GameWorldDataClass()
{
    for (auto hordeData : HordeDataMap)
    {
		delete hordeData.Value;
    }
	HordeDataMap.Empty();
}
void GameWorldDataClass::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("GameWorldDataClass");

		Writer->WriteObjectStart("HordeDataMap");
		for (auto temHordeData : HordeDataMap)
		{
			temHordeData.Value->Serialization(Writer);
		}
		Writer->WriteObjectEnd();//HordeDataMap
	Writer->WriteObjectEnd();//GameWorldDataClass
}
void GameWorldDataClass::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
	TSharedPtr<FJsonObject> JHordeDataMap = JsonObject->GetObjectField("HordeDataMap");
	for (auto jPair : JHordeDataMap->Values)
	{
		FString DataClass = jPair.Key;
		HordeDataClass * Data = (HordeDataClass*)(ClassReflectManager::Get()->GetClassByName(TCHAR_TO_UTF8(*DataClass)));
		if (Data)
		{
			Data->Deserialization(jPair.Value->AsObject());
			HordeDataMap.Add(Data->GetObjectId(), Data);
		}
	}
    
}
void GameWorldDataClass::InitWorldData()
{
	if (HordeDataMap.Num() == 0)
	{
		HordeDataClass * TemHordeData = CreateHordeData();

	}
}
void GameWorldDataClass::InitUserData(UserDataClass * userData)
{
	HordeDataClass * userHordeData = nullptr;
	if (HordeIdIsValid(userData->GetHordeId()))
	{
		userHordeData = HordeDataMap[userData->GetHordeId()];
	}
	else
	{
		userHordeData = CreateHordeData();
		userData->hordeId = userHordeData->GetObjectId();
	}
	userData->hordeData = userHordeData;
}
HordeDataClass * GameWorldDataClass::CreateHordeData()
{
	HordeDataClass * resData = new HordeDataClass();
	HordeDataMap.Add(resData->GetObjectId(), resData);
	return resData;
}
HordeDataClass * GameWorldDataClass::GetHordeDataById(FGuid hordeId)
{
	return HordeDataMap[hordeId];
}
bool GameWorldDataClass::HordeIdIsValid(FGuid hordeId)
{
	return hordeId.IsValid() && HordeDataMap.Contains(hordeId);
}
bool GameWorldDataClass::DestroyHordeId(FGuid hordeId)
{
	if (HordeDataMap.Contains(hordeId))
	{
		delete HordeDataMap[hordeId];
		HordeDataMap.Remove(hordeId);
		return true;
	}
	return false;
}

