
#include "FoodStoreDataClass.h"
#include "FoodStoreActor.h"
#include "GameDataManager.h"


G_REGISTER_CLASS(FoodStoreDataClass)

FoodStoreDataClass::FoodStoreDataClass()
{
	BuildingType = B_FoodStore;
	CropNum = 0;
	BreadNum = 0;
	FruitNum = 0;
}
FoodStoreDataClass::~FoodStoreDataClass()
{
    
}
void FoodStoreDataClass::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("FoodStoreDataClass");
	BaseBuildingDataClass::Serialization(Writer);

	Writer->WriteValue("CropNum", CropNum);
	Writer->WriteValue("BreadNum", BreadNum);
	Writer->WriteValue("FruitNum", FruitNum);

	Writer->WriteObjectEnd();// FoodStoreDataClass
    
}
void FoodStoreDataClass::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
	BaseBuildingDataClass::Deserialization(JsonObject->GetObjectField("BaseBuildingDataClass"));

	CropNum = JsonObject->GetIntegerField("CropNum");
	BreadNum = JsonObject->GetIntegerField("BreadNum");
	FruitNum = JsonObject->GetIntegerField("FruitNum");
    
}
bool FoodStoreDataClass::SpawnBuildingActor(UWorld * world, const FVector & Location, const FRotator & Rotation)
{
	FTransform SpawnTF(Rotation, Location);
	BuildingActor = world->SpawnActorDeferred<AFoodStoreActor>(AFoodStoreActor::StaticClass(), SpawnTF, nullptr, nullptr
		, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	FString MeshName = FString::Printf(TEXT("Mesh%s0"), *BuildingName);
	if (BuildingActor && BuildingActor->SetMeshComponentByIconName(MeshName))
	{
		BuildingActor->SetBuildingData(this);
		BuildingActor->FinishSpawning(SpawnTF);
		return true;
	}
	return false;
}
void FoodStoreDataClass::ChangeFoodNum(int32 plusCrop /* = 0 */, int32 plusBreak /* = 0 */, int32 plusFruit /* = 0 */)
{
	CropNum += plusCrop;
	BreadNum += plusBreak;
	FruitNum += plusFruit;

	GameDataManager::GetInstance()->FoodDataChangedDelegate.Broadcast();
}
void FoodStoreDataClass::GetFoodNum(int32 & OutCropNum, int32 & OutBreadNum, int32 & OutFruitNuM)
{
	OutCropNum = CropNum;
	OutBreadNum = BreadNum;
	OutFruitNuM = FruitNum;
}
