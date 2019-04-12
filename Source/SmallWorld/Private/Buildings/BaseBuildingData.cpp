#include "BaseBuildingData.h"

void BaseBuildingData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("BaseBuilding");
	Writer->WriteValue("Health", Health);
	Writer->WriteValue("Level", Level);

	Writer->WriteObjectEnd();//BaseBuilding
}
void BaseBuildingData::Deserialization(TSharedPtr<FJsonObject> JsonObject)
{
	Health = JsonObject->GetNumberField("Health");
	Level = JsonObject->GetIntegerField("Level");


}