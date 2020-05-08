#pragma once
#include "DataR.h"
#include "CoreMinimal.h"
#include "GameConfig.h"
#include "GameConfigData.h"
#include "ProgressManager.h"


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


class BaseBuildingData : public DataR
{
public:
	friend class ABaseBuildingActor;

    BaseBuildingData();
	~BaseBuildingData();

	virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
	virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;

	virtual void CalculateData(){}
	virtual bool SpawnBuildingActor(UWorld * world, const FVector & Location, const FRotator & Rotation) { return false; };

	void	SetConfigDataByName(FString InName);

	inline bool IsMaxLevel() { return BuildingLevel == ConfigData.maxlevel; }
	inline const SBuildingConfig & GetConfigData() { return ConfigData; }
	inline FString GetBuildingName() { return BuildingName; }
	inline EBuildingType GetBuildingType() { return BuildingType; }
protected:
	//Config Data
	FString			BuildingName;
	EBuildingType	BuildingType;
public:
	// Running Datas
	class HordeData *	BuildingBelongHorde;
	class ABaseBuildingActor * BuildingActor;

	SBuildingConfig  ConfigData;
	FVector			BuildingPosition;
	FRotator		BuildingRotator;

	int32			MaxHealth;
	int32			MaxUpdateTime;

	float	    BuildingHealth;
	int32		BuildingLevel;

	bool		IsUpdating;
	int32		RemainingUpdateTime; // second

};
