#pragma once
#include "DataR.h"
#include "GameConfigData.h"


enum ESoldierType : int32
{
	S_None,
	S_Archer,
	S_Footman,
	S_Griffin,
	S_Horseman,
	S_Knight,
	S_Mage,
	S_SiegeEngine,
	S_Peasant,
};

class BaseSoldierData : public DataR
{
public:
	friend class ASoldierPawn;

	BaseSoldierData();
	~BaseSoldierData();

	virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
	virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;

	virtual bool SpawnSoldierActor(UWorld * world, const FVector & Location, const FRotator & Rotation) { return false; };


	void SetSoldierConfigByName(FString InName);

	inline bool	IsMaxLevel() { return Level == ConfigData.maxlevel; }
	inline FString GetSoldierName() { return SoldierName; }
	inline const SSoldierConfig & GetConfigData() { return ConfigData; }
	inline ESoldierType GetSoldierType() { return SoldierType; }
protected:
	class ASoldierPawn * SoldierPawn;
	class ArmyCenterData * ArmyCenter;

	FString			SoldierName;
	SSoldierConfig  ConfigData;
	ESoldierType	SoldierType;

	float	Health;
	int32	Level;

};
