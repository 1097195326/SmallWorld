#include "BaseBuildingDataClass.h"
#include "GameDataManager.h"
#include "HordeDataClass.h"


BaseBuildingDataClass::BaseBuildingDataClass()
{

	BuildingType = B_None;

	BuildingLevel = 0;
	BuildingHealth = 0.f;
	IsUpdating = false;
	RemainingUpdateTime = 0;
	BuildingActor = nullptr;
}
BaseBuildingDataClass::~BaseBuildingDataClass()
{
	BuildingActor->BeginDestroy();
	BuildingActor = nullptr;

}

void BaseBuildingDataClass::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("BaseBuildingDataClass");
	RuntimeDataClass::Serialization(Writer);

	Writer->WriteValue("BuildingName", *BuildingName);
	Writer->WriteValue("BuildingTransform", BuildingTransform.ToString());
	Writer->WriteValue("BuildingHealth", BuildingHealth);
	Writer->WriteValue("BuildingLevel", BuildingLevel);
	Writer->WriteValue("IsUpdating", IsUpdating);
	Writer->WriteValue("RemainingUpdateTime", RemainingUpdateTime);

	Writer->WriteObjectEnd();//BaseBuildingDataClass
}
void BaseBuildingDataClass::Deserialization(TSharedPtr<FJsonObject> JsonObject)
{
	RuntimeDataClass::Deserialization(JsonObject->GetObjectField("RuntimeDataClass"));

	BuildingName = JsonObject->GetStringField("BuildingName");
	BuildingTransform.InitFromString(JsonObject->GetStringField("BuildingTransform"));
	BuildingHealth = JsonObject->GetNumberField("BuildingHealth");
	BuildingLevel = JsonObject->GetIntegerField("BuildingLevel");
	IsUpdating = JsonObject->GetBoolField("IsUpdating");
	RemainingUpdateTime = JsonObject->GetIntegerField("RemainingUpdateTime");

	SetConfigDataByName(BuildingName);

	SpawnBuildingActor(GEngine->GetWorld(), BuildingTransform, BuildingLevel);
}
HordeDataClass * BaseBuildingDataClass::GetHordeBelongTo()
{
	return HordeBelongTo;//GameDataManager::GetInstance()->GetGameWorldData()->GetHordeDataById(GetParentId());
}
void BaseBuildingDataClass::SetHordeBelongTo(HordeDataClass * InHorde)
{
	HordeBelongTo = InHorde;
}
void BaseBuildingDataClass::SetConfigDataByName(FString InName)
{
	BuildingName = InName;
	BuildingConfig = GameDataManager::GetInstance()->GetGameConfigData()->GetBuildingConfig(BuildingName);
}
bool BaseBuildingDataClass::IsUserData()
{
	return GameDataManager::GetInstance()->IsUserHordeData(HordeBelongTo);
}