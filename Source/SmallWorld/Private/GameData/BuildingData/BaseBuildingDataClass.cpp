#include "BaseBuildingDataClass.h"
#include "GameDataManager.h"
#include "HordeDataClass.h"


BaseBuildingDataClass::BaseBuildingDataClass()
{

	BuildingType = B_None;
	BuildingPosition = FVector::ZeroVector;
	BuildingRotator = FRotator::ZeroRotator;

	BuildingLevel = 0;
	BuildingHealth = 0.f;
	IsUpdating = false;
	RemainingUpdateTime = 0;
	BuildingBelongHorde = nullptr;
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
	Writer->WriteValue("BuildingPosition", BuildingPosition.ToString());
	Writer->WriteValue("BuildingRotator", BuildingRotator.ToString());
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
	BuildingPosition.InitFromString(JsonObject->GetStringField("BuildingPosition"));
	BuildingRotator.InitFromString(JsonObject->GetStringField("BuildingRotator"));
	BuildingHealth = JsonObject->GetNumberField("BuildingHealth");
	BuildingLevel = JsonObject->GetIntegerField("BuildingLevel");
	IsUpdating = JsonObject->GetBoolField("IsUpdating");
	RemainingUpdateTime = JsonObject->GetIntegerField("RemainingUpdateTime");

	SetConfigDataByName(BuildingName);
}
void BaseBuildingDataClass::SetConfigDataByName(FString InName)
{
	BuildingName = InName;
	SoldierConfig = GameDataManager::GetInstance()->GetGameConfigData()->GetBuildingConfig(BuildingName);
}

