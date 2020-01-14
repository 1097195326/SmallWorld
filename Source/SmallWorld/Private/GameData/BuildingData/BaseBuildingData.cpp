#include "BaseBuildingData.h"



BaseBuildingData::BaseBuildingData()
{
	BuildingPosition = FVector::ZeroVector;
	BuildingRotator = FRotator::ZeroRotator;

    BuildingLevel = 0;
	BuildingHealth = 0.f;
    BuildingType = B_None;

}
void BaseBuildingData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("BaseBuildingData");
	DataR::Serialization(Writer);

	Writer->WriteValue("BuildingHealth", BuildingHealth);
	Writer->WriteValue("BuildingLevel", BuildingLevel);
    Writer->WriteValue("BuildingPosition",BuildingPosition.ToString());
	Writer->WriteValue("BuildingRotator", BuildingRotator.ToString());
	Writer->WriteObjectEnd();//BaseBuildingData
}
void BaseBuildingData::Deserialization(TSharedPtr<FJsonObject> JsonObject)
{
	DataR::Deserialization(JsonObject->GetObjectField("DataR"));

	BuildingHealth = JsonObject->GetNumberField("BuildingHealth");
	BuildingLevel = JsonObject->GetIntegerField("BuildingLevel");
	BuildingPosition.InitFromString(JsonObject->GetStringField("BuildingPosition"));
	BuildingRotator.InitFromString(JsonObject->GetStringField("BuildingRotator"));
    
}
