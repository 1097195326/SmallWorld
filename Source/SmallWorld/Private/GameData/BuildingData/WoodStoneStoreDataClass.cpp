
#include "WoodStoneStoreDataClass.h"
#include "WoodStoneStoreActor.h"
#include "GameDataManager.h"


G_REGISTER_CLASS(WoodStoneStoreDataClass)

WoodStoneStoreDataClass::WoodStoneStoreDataClass()
{
	BuildingType = B_WoodStoneStore;
	WoodNum = 0;
	StoneNum = 0;

}
WoodStoneStoreDataClass::~WoodStoneStoreDataClass()
{
    
}
void WoodStoneStoreDataClass::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("WoodStoneStoreDataClass");
	BaseBuildingDataClass::Serialization(Writer);

	Writer->WriteValue("WoodNum", WoodNum);
	Writer->WriteValue("StoneNum", StoneNum);

	Writer->WriteObjectEnd();// WoodStoneStoreDataClass
    
}
void WoodStoneStoreDataClass::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
	BaseBuildingDataClass::Deserialization(JsonObject->GetObjectField("BaseBuildingDataClass"));

	WoodNum = JsonObject->GetIntegerField("WoodNum");
	StoneNum = JsonObject->GetIntegerField("StoneNum");

    
}
bool WoodStoneStoreDataClass::SpawnBuildingActor(UWorld * world, const FVector & Location, const FRotator & Rotation)
{
	FTransform SpawnTF(Rotation, Location);
	BuildingActor = world->SpawnActorDeferred<AWoodStoneStoreActor>(AWoodStoneStoreActor::StaticClass(), SpawnTF, nullptr, nullptr
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
void WoodStoneStoreDataClass::ChangeWoodNum(const int32 & plusWood)
{
	WoodNum += plusWood;
	WoodNum = WoodNum < 0 ? 0 : WoodNum;
	if (plusWood != 0)
	{
		GameDataManager::GetInstance()->WoodDataChangedDelegate.Broadcast();
	}
}
void WoodStoneStoreDataClass::ChangeStoneNum(const int32 & plusStone)
{
	StoneNum += plusStone;
	StoneNum = StoneNum < 0 ? 0 : StoneNum;
	if (plusStone != 0)
	{
		GameDataManager::GetInstance()->StoneDataChangedDelegate.Broadcast();
	}
}