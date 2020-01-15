#include "FruitFarmData.h"

G_REGISTER_CLASS(FruitFarmData)


FruitFarmData::FruitFarmData()
{
	BuildingType = B_FruitFarm;
	FruitNum = 0;
}
FruitFarmData::~FruitFarmData()
{

}
void FruitFarmData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("FruitFarmData");
	BaseBuildingData::Serialization(Writer);

	Writer->WriteValue("FruitNum", FruitNum);

	Writer->WriteObjectEnd();// FruitFarmData

}
void FruitFarmData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
	BaseBuildingData::Deserialization(JsonObject->GetObjectField("BaseBuildingData"));

	FruitNum = JsonObject->GetIntegerField("FruitNum");


}
bool FruitFarmData::IsFull()
{
	return false;
}