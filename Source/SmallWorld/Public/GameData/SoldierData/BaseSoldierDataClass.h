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

	bool IsUserData();

	void SetSoldierConfigByName(FString InName);
	
	inline bool	IsFullLevel() { return CurrentLevel == SoldierConfig.maxlevel; }
	inline bool IsFullMovePower() { return CurrentMovePower == GetLevelInfo().restoremovability; }
	inline bool IsFullHealth() { return CurrentHealth == GetLevelInfo().restorehealth; }
	inline bool IsFullAttackPower() { return CurrentAttackPower == GetAttackSpeed(); }
	
	inline FString GetSoldierName() { return SoldierName; }
	inline SoldierTypeEnum GetSoldierType() { return SoldierType; }
	inline const SoldierConfigStruct & GetSoldierConfig() { return SoldierConfig; }
	inline const SoldierLevelInfoStruct & GetLevelInfo() const { return SoldierConfig.LevelInfos[CurrentLevel]; }

	inline float GetCurrentMovePower() const { return CurrentMovePower; }
	inline float GetCurrentHealth() const { return CurrentHealth; }
	inline float GetCurrentAttackPower() const { return CurrentAttackPower; }

	inline int32 GetMovability() const { return SoldierConfig.movability; }
	inline int32 GetVisibility() const { return SoldierConfig.visibility; }
	inline int32 GetAttackrange() const { return SoldierConfig.attackrange; }
	inline float GetAttackSpeed() const { return SoldierConfig.attackspeed; }

protected:
	class ASoldierPawn * SoldierPawn;
	class CommandCenterDataClass * CommandCenter;

	FString SoldierName;
	SoldierTypeEnum SoldierType;
	SoldierConfigStruct SoldierConfig;

	float CurrentHealth;
	float CurrentMovePower;
	float CurrentAttackPower;

	int32 CurrentLevel;

};
