#include "BaseSoldierDataClass.h"
#include "GameDataManager.h"
#include "CommandCenterDataClass.h"
#include "HordeDataClass.h"

BaseSoldierDataClass::BaseSoldierDataClass()
{
	SoldierType = Soldier_None;
	SoldierPawn = nullptr;
	CommandCenter = nullptr;
	Level = -1;
	Health = 0.f;

}
BaseSoldierDataClass::~BaseSoldierDataClass()
{
	if (SoldierPawn)
	{
		SoldierPawn->BeginDestroy();
		SoldierPawn = nullptr;
	}

}
void BaseSoldierDataClass::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("BaseSoldierDataClass");
	RuntimeDataClass::Serialization(Writer);

	if (CommandCenter)
	{
		Writer->WriteValue("ArmyCenterID", CommandCenter->GetObjectId().ToString());
	}
	Writer->WriteValue("SoldierName", *SoldierName);
	Writer->WriteValue("Health", Health);
	Writer->WriteValue("Level", Level);

	Writer->WriteObjectEnd();
}
void BaseSoldierDataClass::Deserialization(TSharedPtr<FJsonObject> JsonObject)
{
	RuntimeDataClass::Deserialization(JsonObject->GetObjectField("RuntimeDataClass"));

	SoldierName = JsonObject->GetStringField("SoldierName");
	Health = JsonObject->GetNumberField("Health");
	Level = JsonObject->GetIntegerField("Level");

	FString ArmyCenterID;
	if (JsonObject->TryGetStringField("ArmyCenterID", ArmyCenterID))
	{

	}

	SetSoldierConfigByName(SoldierName);
}
void BaseSoldierDataClass::SetCommandCenter(class CommandCenterDataClass * InCommandCenter)
{
	CommandCenter = InCommandCenter;
}
CommandCenterDataClass * BaseSoldierDataClass::GetCommandCenter()
{
	return CommandCenter;
}
void BaseSoldierDataClass::SetSoldierConfigByName(FString InName)
{
	SoldierName = InName;
	SoldierConfig = GameDataManager::GetInstance()->GetGameConfigData()->GetSoldierConfig(InName);
}