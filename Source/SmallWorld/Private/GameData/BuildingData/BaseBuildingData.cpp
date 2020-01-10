#include "BaseBuildingData.h"



BaseBuildingData::BaseBuildingData()
{
    
    BuildingLevel = 0;
    BuildingType = B_None;

}
void BaseBuildingData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("BaseBuilding");
	Writer->WriteValue("BuildingHealth", BuildingHealth);
	Writer->WriteValue("BuildingLevel", BuildingLevel);
    Writer->WriteValue("BuildingPosition",BuildingPosition.ToString());
	Writer->WriteObjectEnd();//BaseBuilding
}
void BaseBuildingData::Deserialization(TSharedPtr<FJsonObject> JsonObject)
{
	BuildingHealth = JsonObject->GetNumberField("BuildingHealth");
	BuildingLevel = JsonObject->GetIntegerField("BuildingLevel");
    BuildingPosition.InitFromString(JsonObject->GetStringField("BuildingPosition"));
    
}
