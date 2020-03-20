
#include "FoodStoreData.h"
#include "FoodStoreActor.h"
#include "DataManager.h"


G_REGISTER_CLASS(FoodStoreData)

FoodStoreData::FoodStoreData()
{
	BuildingType = B_FoodStore;
	CropNum = 0;
	BreadNum = 0;
	FruitNum = 0;
}
FoodStoreData::~FoodStoreData()
{
    
}
void FoodStoreData::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("FoodStoreData");
	BaseBuildingData::Serialization(Writer);

	Writer->WriteValue("CropNum", CropNum);
	Writer->WriteValue("BreadNum", BreadNum);
	Writer->WriteValue("FruitNum", FruitNum);

	Writer->WriteObjectEnd();// FoodStoreData
    
}
void FoodStoreData::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
	BaseBuildingData::Deserialization(JsonObject->GetObjectField("BaseBuildingData"));

	CropNum = JsonObject->GetIntegerField("CropNum");
	BreadNum = JsonObject->GetIntegerField("BreadNum");
	FruitNum = JsonObject->GetIntegerField("FruitNum");
    
}
bool FoodStoreData::SpawnBuildingActor(UWorld * world, const FVector & Location, const FRotator & Rotation)
{

	return false;
}
void FoodStoreData::ChangeFoodNum(int32 plusCrop /* = 0 */, int32 plusBreak /* = 0 */, int32 plusFruit /* = 0 */)
{
	CropNum += plusCrop;
	BreadNum += plusBreak;
	FruitNum += plusFruit;

	DataManager::GetInstance()->FoodDataChangedDelegate.Broadcast();
}
void FoodStoreData::GetFoodNum(int32 & OutCropNum, int32 & OutBreadNum, int32 & OutFruitNuM)
{
	OutCropNum = CropNum;
	OutBreadNum = BreadNum;
	OutFruitNuM = FruitNum;
}
