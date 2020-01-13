#include "FruitFarmData.h"

G_REGISTER_CLASS(FruitFarmData)


FruitFarmData::FruitFarmData()
{
	BuildingType = B_FruitFarm;
}
FruitFarmData::~FruitFarmData()
{

}
void FruitFarmData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("FruitFarmData");
	BaseBuildingData::Serialization(Writer);



	Writer->WriteObjectEnd();// FruitFarmData

}
void FruitFarmData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{


}