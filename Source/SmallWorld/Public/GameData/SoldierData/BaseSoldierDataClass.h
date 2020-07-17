#pragma once
#include "RuntimeDataClass.h"
#include "GameConfigDataClass.h"
#include "SoldierPawn.h"



enum SoldierTypeEnum : int32
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

	inline bool	IsMaxLevel() { return Level == SoldierConfig.maxlevel; }
	inline FString GetSoldierName() { return SoldierName; }
	inline const SoldierConfigStruct & GetSoldierConfig() { return SoldierConfig; }
	inline SoldierTypeEnum GetSoldierType() { return SoldierType; }
	inline int32 GetMovePower() const { return MovePower; }
	inline int32 GetMoveDistance() const { return SoldierConfig.distance; }
protected:
	class ASoldierPawn *		SoldierPawn;
	class ArmyCenterDataClass * ArmyCenter;

	FString					SoldierName;
	SoldierConfigStruct		SoldierConfig;
	SoldierTypeEnum			SoldierType;

	float	Health;
	int32	Level;
	int32	MovePower;

};
