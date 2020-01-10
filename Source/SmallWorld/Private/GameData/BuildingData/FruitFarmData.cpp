#include "FruitFarmData.h"



FruitFarmData::FruitFarmData()
{
	BuildingType = B_FruitFarm;
}
FruitFarmData::~FruitFarmData()
{

}
void FruitFarmData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{


}
void FruitFarmData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{


}