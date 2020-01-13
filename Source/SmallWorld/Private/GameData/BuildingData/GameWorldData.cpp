
#include "GameWorldData.h"
#include "UserData.h"

GameWorldData::GameWorldData()
{
    
}
GameWorldData::~GameWorldData()
{
    
}
void GameWorldData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("GameWorldData");

		Writer->WriteObjectStart("HordeDatas");
		for (auto temHordeData : HordeDatas)
		{
			temHordeData->Serialization(Writer);
		}
		Writer->WriteObjectEnd();//HordeDatas
	Writer->WriteObjectEnd();//GameWorldData
}
void GameWorldData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
	TSharedPtr<FJsonObject> JHordeDatas = JsonObject->GetObjectField("HordeDatas");
	for (auto jPair : JHordeDatas->Values)
	{
		FString DataClass = jPair.Key;
		HordeData * Data = (HordeData*)(ReflectManager::Get()->GetClassByName(TCHAR_TO_UTF8(*DataClass)));
		if (Data)
		{
			Data->Deserialization(jPair.Value->AsObject());
			HordeDatas.Add(Data);
		}
	}
    
}
void GameWorldData::InitUserData(UserData * userData)
{
	HordeData * userHordeData = nullptr;
	if (!userData->GetHordeId().IsValid())
	{
		userHordeData = new HordeData();
		userData->SetHordeId(userHordeData->GetID());
	}
	
	userData->SetHordeData(userHordeData);

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

