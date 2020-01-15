#include "HouseData.h"
#include "DataManager.h"


G_REGISTER_CLASS(HouseData)

HouseData::HouseData()
{
	BuildingType = B_House;
	PeopleNum = 0;

}
HouseData::~HouseData()
{
    
}
void HouseData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("HouseData");
	BaseBuildingData::Serialization(Writer);
	
	Writer->WriteValue("PeopleNum", PeopleNum);

	Writer->WriteObjectEnd();// HouseData
    
}
void HouseData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
	BaseBuildingData::Deserialization(JsonObject->GetObjectField("BaseBuildingData"));

	PeopleNum = JsonObject->GetIntegerField("PeopleNum");
    
}
void HouseData::ChangePeopleNum(int32 plusNum)
{
	PeopleNum += plusNum;
	DataManager::GetInstance()->PeopleDataChangedDelegate.Broadcast();
}
