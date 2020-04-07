#include "BaseBuildingData.h"
#include "DataManager.h"
#include "HordeData.h"
#include "BaseBuildingActor.h"


BaseBuildingData::BaseBuildingData()
{
	GDataType = GData::Building;

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
BaseBuildingData::~BaseBuildingData()
{
	BuildingActor->BeginDestroy();
	BuildingActor = nullptr;

}

void BaseBuildingData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("BaseBuildingData");
	DataR::Serialization(Writer);

	Writer->WriteValue("BuildingName", *BuildingName);
	Writer->WriteValue("BuildingPosition", BuildingPosition.ToString());
	Writer->WriteValue("BuildingRotator", BuildingRotator.ToString());
	Writer->WriteValue("BuildingHealth", BuildingHealth);
	Writer->WriteValue("BuildingLevel", BuildingLevel);
	Writer->WriteValue("IsUpdating", IsUpdating);
	Writer->WriteValue("RemainingUpdateTime", RemainingUpdateTime);

	Writer->WriteObjectEnd();//BaseBuildingData
}
void BaseBuildingData::Deserialization(TSharedPtr<FJsonObject> JsonObject)
{
	DataR::Deserialization(JsonObject->GetObjectField("DataR"));

	BuildingName = JsonObject->GetStringField("BuildingName");
	BuildingPosition.InitFromString(JsonObject->GetStringField("BuildingPosition"));
	BuildingRotator.InitFromString(JsonObject->GetStringField("BuildingRotator"));
	BuildingHealth = JsonObject->GetNumberField("BuildingHealth");
	BuildingLevel = JsonObject->GetIntegerField("BuildingLevel");
	IsUpdating = JsonObject->GetBoolField("IsUpdating");
	RemainingUpdateTime = JsonObject->GetIntegerField("RemainingUpdateTime");

}
void BaseBuildingData::SetConfigDataByName(FString InName)
{
	BuildingName = InName;
	ConfigData = DataManager::GetInstance()->GetGameConfigData()->GetBuildingConfig(BuildingName);
}

