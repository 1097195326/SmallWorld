
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
		for (int i = 0;i < RaceEnum::Race_Num; i++ )
		{
			CreateHordeData((RaceEnum)i);
		}
	}
}
void GameWorldDataClass::InitUserData(UserDataClass * InUserData)
{
	if (HordeIdIsValid(InUserData->GetHordeId()))
	{
		InUserData->HordeData = HordeDataMap[InUserData->GetHordeId()];
	}
}
void GameWorldDataClass::SetUserDataRace(class UserDataClass * InUserData, RaceEnum InRace)
{
	TArray<HordeDataClass *> TemHordeArray = GetHordeDatByRace(InRace);
	HordeDataClass * TemHordeData = TemHordeArray[0];
	InUserData->HordeId = TemHordeData->GetObjectId();
	InUserData->HordeData = TemHordeData;
}
HordeDataClass * GameWorldDataClass::CreateHordeData(RaceEnum InRace)
{
	HordeDataClass * resData = new HordeDataClass(InRace);
	HordeDataMap.Add(resData->GetObjectId(), resData);
	return resData;
}
HordeDataClass * GameWorldDataClass::GetHordeDataById(const FGuid & InHordeId)
{
	return HordeDataMap[InHordeId];
}
TArray<HordeDataClass*> GameWorldDataClass::GetHordeDatByRace(RaceEnum InRace)
{
	TArray<HordeDataClass*> TemArray;
	for (auto TemIter : HordeDataMap)
	{
		if (TemIter.Value->GetRace() == InRace)
		{
			TemArray.Add(TemIter.Value);
		}
	}
	return MoveTemp(TemArray);
}
bool GameWorldDataClass::HordeIdIsValid(const FGuid & InHordeId)
{
	return InHordeId.IsValid() && HordeDataMap.Contains(InHordeId);
}
bool GameWorldDataClass::DestroyHordeId(const FGuid & InHordeId)
{
	if (HordeDataMap.Contains(InHordeId))
	{
		delete HordeDataMap[InHordeId];
		HordeDataMap.Remove(InHordeId);
		return true;
	}
	return false;
}

