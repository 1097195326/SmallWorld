
#include "WoodStoneStoreData.h"
#include "DataManager.h"


G_REGISTER_CLASS(WoodStoneStoreData)

WoodStoneStoreData::WoodStoneStoreData()
{
	BuildingType = B_WoodStoneStore;
	WoodNum = 0;
	StoneNum = 0;

}
WoodStoneStoreData::~WoodStoneStoreData()
{
    
}
void WoodStoneStoreData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("WoodStoneStoreData");
	BaseBuildingData::Serialization(Writer);

	Writer->WriteValue("WoodNum", WoodNum);
	Writer->WriteValue("StoneNum", StoneNum);

	Writer->WriteObjectEnd();// WoodStoneStoreData
    
}
void WoodStoneStoreData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
	BaseBuildingData::Deserialization(JsonObject->GetObjectField("BaseBuildingData"));

	WoodNum = JsonObject->GetIntegerField("WoodNum");
	StoneNum = JsonObject->GetIntegerField("StoneNum");

    
}

void WoodStoneStoreData::ChangeWoodNum(const int32 & plusWood)
{
	WoodNum += plusWood;
	WoodNum = WoodNum < 0 ? 0 : WoodNum;
	if (plusWood != 0)
	{
		DataManager::GetInstance()->WoodDataChangedDelegate.Broadcast();
	}
}
void WoodStoneStoreData::ChangeStoneNum(const int32 & plusStone)
{
	StoneNum += plusStone;
	StoneNum = StoneNum < 0 ? 0 : StoneNum;
	if (plusStone != 0)
	{
		DataManager::GetInstance()->StoneDataChangedDelegate.Broadcast();
	}
}