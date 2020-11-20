#include "HouseDataClass.h"
#include "HouseActor.h"
#include "GameDataManager.h"


G_REGISTER_CLASS(HouseDataClass)

HouseDataClass::HouseDataClass()
{
	BuildingType = B_House;
	PeopleNum = 0;

}
HouseDataClass::~HouseDataClass()
{
    
}
void HouseDataClass::Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer)
{
	Writer->WriteObjectStart("HouseDataClass");
	BaseBuildingDataClass::Serialization(Writer);
	
	Writer->WriteValue("PeopleNum", PeopleNum);

	Writer->WriteObjectEnd();// HouseDataClass
    
}
void HouseDataClass::Deserialization(TSharedPtr<FJsonObject>  JsonObject)
{
	BaseBuildingDataClass::Deserialization(JsonObject->GetObjectField("BaseBuildingDataClass"));

	PeopleNum = JsonObject->GetIntegerField("PeopleNum");
    
}
ABaseBuildingActor * HouseDataClass::SpawnBuildingActor(UWorld * world, const FTransform & SpawnTF, const int32 && InIndex)
{
	FActorSpawnParameters Paramerter;
	Paramerter.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	BuildingActor = world->SpawnActor<AHouseActor>(AHouseActor::StaticClass(), SpawnTF, Paramerter);
	FString MeshName = FString::Printf(TEXT("Mesh%s%d"), *BuildingName, InIndex);
	if (BuildingActor && BuildingActor->SetMeshComponentByIconName(MeshName))
	{
		BuildingActor->SetBuildingData(this);
	}
	return BuildingActor;
}
void HouseDataClass::ChangePeopleNum(int32 plusNum)
{
	PeopleNum += plusNum;
	GameDataManager::GetInstance()->PeopleDataChangedDelegate.Broadcast();
}
