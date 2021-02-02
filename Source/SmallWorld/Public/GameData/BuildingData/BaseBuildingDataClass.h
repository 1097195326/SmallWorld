#pragma once
#include "RuntimeDataClass.h"
#include "CoreMinimal.h"
#include "BaseSoldierDataClass.h"
#include "ProgressManager.h"
#include "BaseBuildingActor.h"


enum EBuildingType
{
	B_None,
	// building
	B_ArmyCenter,
	B_Bakery,
	B_CommandCenter,
	B_Farm,
	B_FoodStore,
	B_FruitFarm,
	B_Gate,
	B_House,
	B_Mill,
	B_MoneyStore,
	B_WoodStoneStore,
	B_Tower,
	B_Wall,

	//
	B_Tree,
	B_Stone,
	B_Mine,

};


class BaseBuildingDataClass : public RuntimeDataClass
{
public:
	friend class ABaseBuildingActor;

    BaseBuildingDataClass();
	~BaseBuildingDataClass();

	virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
	virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;

	virtual void CalculateData(){}
	virtual ABaseBuildingActor * SpawnBuildingActor(UWorld * world, const FTransform & SpawnTF, const int32 & InIndex) { return nullptr; };
	ABaseBuildingActor * GetBuildingActor() { return BuildingActor; }

	bool IsUserData();
	class HordeDataClass * GetHordeBelongTo();
	void SetHordeBelongTo(class HordeDataClass * InHorde);

	void SetConfigDataByName(FString InName);

	inline bool IsFullLevel() { return BuildingLevel == BuildingConfig.MaxLevel; }
	inline const BuildingConfigStruct & GetBuildingConfig() { return BuildingConfig; }
	inline const BuildingLevelInfoStruct & GetLevelInfo() { return BuildingConfig.LevelInfos[BuildingLevel]; }

	inline FString GetBuildingName() { return BuildingName; }
	inline EBuildingType GetBuildingType() { return BuildingType; }
protected:
	class HordeDataClass * HordeBelongTo;
	//Config Data
	FString BuildingName;
	EBuildingType BuildingType;
public:
	// Running Datas
	class ABaseBuildingActor * BuildingActor;

	BuildingConfigStruct BuildingConfig;
	FTransform BuildingTransform;
	FVector BuildingPosition;
	FRotator BuildingRotator;

	int32 MaxHealth;
	int32 MaxUpdateTime;

	float BuildingHealth;
	int32 BuildingLevel;

	bool IsUpdating;
	int32 RemainingUpdateTime; // second

};
