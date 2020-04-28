#include "BaseSoldierData.h"
#include "DataManager.h"
#include "SoldierPawn.h"
#include "ArmyCenterData.h"

BaseSoldierData::BaseSoldierData()
{
	SoldierType = S_None;
	SoldierPawn = nullptr;
	ArmyCenter = nullptr;
	Level = -1;
	Health = 0.f;

}
BaseSoldierData::~BaseSoldierData()
{
	if (SoldierPawn)
	{
		SoldierPawn->BeginDestroy();
		SoldierPawn = nullptr;
	}

}
void BaseSoldierData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("BaseSoldierData");
	DataR::Serialization(Writer);

	if (ArmyCenter)
	{
		Writer->WriteValue("ArmyCenterID", ArmyCenter->GetID().ToString());
	}
	Writer->WriteValue("SoldierName", *SoldierName);
	Writer->WriteValue("Health", Health);
	Writer->WriteValue("Level", Level);

	Writer->WriteObjectEnd();
}
void BaseSoldierData::Deserialization(TSharedPtr<FJsonObject> JsonObject)
{
	DataR::Deserialization(JsonObject->GetObjectField("DataR"));

	SoldierName = JsonObject->GetStringField("SoldierName");
	Health = JsonObject->GetNumberField("Health");
	Level = JsonObject->GetIntegerField("Level");

	FString ArmyCenterID;
	if (JsonObject->TryGetStringField("ArmyCenterID", ArmyCenterID))
	{

	}

	SetSoldierConfigByName(SoldierName);
}
void BaseSoldierData::SetSoldierConfigByName(FString InName)
{
	SoldierName = InName;
	ConfigData = DataManager::GetInstance()->GetGameConfigData()->GetSoldierConfig(InName);
}