#pragma once
#include "RuntimeDataClass.h"
#include "GameConfigDataClass.h"
#include "SoldierPawn.h"



class BaseSoldierDataClass : public RuntimeDataClass
{
public:
	friend class ASoldierPawn;

	BaseSoldierDataClass();
	~BaseSoldierDataClass();

	virtual void Serialization(TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer) override;
	virtual void Deserialization(TSharedPtr<FJsonObject>  JsonObject) override;

	virtual ASoldierPawn * SpawnSoldierActor(const FString & InSoldierName);
	virtual void DestroySoldier();

	class CommandCenterDataClass * GetCommandCenter();
	void SetCommandCenter(class CommandCenterDataClass * InCommandCenter);


	void SetSoldierConfigByName(FString InName);
	
	inline bool	IsMaxLevel() { return CurrentLevel == SoldierConfig.maxlevel; }
	inline FString GetSoldierName() { return SoldierName; }
	inline const SoldierConfigStruct & GetSoldierConfig() { return SoldierConfig; }
	inline SoldierTypeEnum GetSoldierType() { return SoldierType; }
	inline bool IsFullMovePower() const { return CurrentMovePower == GetMovability(); }
	inline int32 GetCurrentMovePower() const { return CurrentMovePower; }
	inline int32 GetMovability() const { return SoldierConfig.movability; }
	inline int32 GetVisibility() const { return SoldierConfig.visibility; }
	inline int32 GetAttackrange() const { return SoldierConfig.attackrange; }
	inline float GetAttackSpeed() const { return SoldierConfig.attackspeed; }

protected:
	class ASoldierPawn * SoldierPawn;
	class CommandCenterDataClass * CommandCenter;

	FString SoldierName;
	SoldierConfigStruct SoldierConfig;
	SoldierTypeEnum SoldierType;

	float CurrentHealth;
	int32 CurrentLevel;
	int32 CurrentMovePower;

};
