
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

void WoodStoneStoreData::ChangeWoodStoneNum(int32 plusWood /* = 0 */, int32 plusStone /* = 0 */)
{
	WoodNum += plusWood;
	StoneNum += plusStone;

	DataManager::GetInstance()->WoodStoneDataChangedDelegate.Broadcast();
}
void WoodStoneStoreData::GetWoodStoneNum(int32 & OutWoodNum, int32 & OutStoneNum)
{
	OutWoodNum = WoodNum;
	OutStoneNum = StoneNum;
}

