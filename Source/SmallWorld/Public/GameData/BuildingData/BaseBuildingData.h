#pragma once
#include "DataR.h"
#include "CoreMinimal.h"
#include "GameConfig.h"



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
    
	virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
	virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;

	virtual FString GetName() { return TEXT(""); }
public:
	FVector     BuildingPosition;
	FRotator    BuildingRotator;
	float	    BuildingHealth;
	int32		    BuildingLevel;
	EBuildingType	BuildingType;

};
