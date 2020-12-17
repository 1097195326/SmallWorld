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
	
	inline bool	IsFullLevel() { return CurrentLevel == SoldierConfig.MaxLevel; }
	inline bool IsFullMovePower() { return CurrentMovePower == GetLevelInfo().Movability; }
	inline bool IsFullHealth() { return CurrentHealth == GetLevelInfo().Health; }
	inline bool IsFullAttackPower() { return CurrentAttackPower == GetAttackSpeed(); }
	
	inline FString GetSoldierName() { return SoldierName; }
	inline SoldierTypeEnum GetSoldierType() { return SoldierType; }
	inline const SoldierConfigStruct & GetSoldierConfig() { return SoldierConfig; }
	inline const SoldierLevelInfoStruct & GetLevelInfo() const { return SoldierConfig.LevelInfos[CurrentLevel]; }

	inline float GetCurrentMovePower() const { return CurrentMovePower; }
	inline float GetCurrentHealth() const { return CurrentHealth; }
	inline float GetCurrentAttackPower() const { return CurrentAttackPower; }

	float SetCurrentMovePower(float InValue)
	{
		CurrentMovePower = InValue;
		if (CurrentMovePower > GetLevelInfo().Movability)
		{
			CurrentMovePower = GetLevelInfo().Movability;
		}
		return CurrentMovePower;
	}
	float SetCurrentHealth(float InValue)
	{
		CurrentHealth = InValue;
		if (CurrentHealth > GetLevelInfo().Health)
		{
			CurrentHealth = GetLevelInfo().Health;
		}
		return CurrentHealth;
	}
	float SetCurrentAttackPower(float InValue)
	{
		CurrentAttackPower = InValue;
		if (CurrentAttackPower > GetAttackSpeed())
		{
			CurrentAttackPower = GetAttackSpeed();
		}
		return CurrentAttackPower;
	}

	inline int32 GetMoveRange() const { return SoldierConfig.MoveRange; }
	inline int32 GetVisibleRange() const { return SoldierConfig.VisibleRange; }
	inline int32 GetAttackRange() const { return SoldierConfig.AttackRange; }
	inline float GetAttackSpeed() const { return SoldierConfig.AttackSpeed; }

protected:
	class ASoldierPawn * SoldierPawn;
	class CommandCenterDataClass * CommandCenter;

	FGuid   CommandCenterId;
	FString SoldierName;
	SoldierTypeEnum SoldierType;
	SoldierConfigStruct SoldierConfig;

	float CurrentHealth;
	float CurrentMovePower;
	float CurrentAttackPower;

	int32 CurrentLevel;

};
