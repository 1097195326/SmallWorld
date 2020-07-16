#pragma once
#include "RuntimeDataClass.h"
#include "GameConfigDataClass.h"
#include "SoldierPawn.h"


enum SoldierEnum : int32
{
	Soldier_None,
	Soldier_Archer,
	Soldier_Footman,
	Soldier_Griffin,
	Soldier_Horseman,
	Soldier_Knight,
	Soldier_Mage,
	Soldier_SiegeEngine,
	Soldier_Peasant,
	Soldier_Num
};

class BaseSoldierDataClass : public RuntimeDataClass
{
public:
	friend class ASoldierPawn;

	BaseSoldierDataClass();
	~BaseSoldierDataClass();

	virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
	virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;

	virtual bool SpawnSoldierActor(UWorld * world, const FVector & Location, const FRotator & Rotation) { return false; };


	void SetSoldierConfigByName(FString InName);

	inline bool	IsMaxLevel() { return Level == ConfigData.maxlevel; }
	inline FString GetSoldierName() { return SoldierName; }
	inline const SSoldierConfig & GetConfigData() { return ConfigData; }
	inline SoldierEnum GetSoldierType() { return SoldierType; }
protected:
	class ASoldierPawn * SoldierPawn;
	class ArmyCenterDataClass * ArmyCenter;

	FString			SoldierName;
	SSoldierConfig  ConfigData;
	SoldierEnum	SoldierType;

	float	Health;
	int32	Level;

};
