#include "BaseBuildingData.h"



BaseBuildingData::BaseBuildingData()
{
    
    mDirection = Dir_None;
    mLevel = 0;
    mType = B_None;
}
void BaseBuildingData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("BaseBuilding");
	Writer->WriteValue("Health", mHealth);
	Writer->WriteValue("Level", mLevel);
    Writer->WriteValue("mPositon",mPosition.ToString());
	Writer->WriteObjectEnd();//BaseBuilding
}
void BaseBuildingData::Deserialization(TSharedPtr<FJsonObject> JsonObject)
{
	mHealth = JsonObject->GetNumberField("mHealth");
	mLevel = JsonObject->GetIntegerField("mLevel");
    mPosition.InitFromString(JsonObject->GetStringField("mPosition"));
    
}
void BaseBuildingData::SetPosition(FVector _position)
{
    mPosition = _position;
}
void BaseBuildingData::SetLevel(int _level)
{
    mLevel = _level;
}
void BaseBuildingData::SetHealth(float _health)
{
    mHealth = _health;
}
