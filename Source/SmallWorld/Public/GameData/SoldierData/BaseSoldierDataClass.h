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
	
	void InitDataWithConfig();

	inline FString GetSoldierName() { return SoldierName; }
	inline SoldierTypeEnum GetSoldierType() { return SoldierType; }
	inline const SoldierConfigStruct & GetSoldierConfig() { return SoldierConfig; }
	inline const SoldierLevelInfoStruct & GetLevelInfo() const { return SoldierConfig.LevelInfos[CurrentLevel]; }

	inline bool	IsFullLevel() { return CurrentLevel == SoldierConfig.MaxLevel; }

	inline bool IsFullHealth() { return CurrentHealth == GetLevelInfo().Health; }
	inline bool IsAlive() { return CurrentHealth > 0.f; }
	void TakeDamage(float InDamage);
	inline float GetCurrentHealth() const { return CurrentHealth; }
	void SetCurrentHealth(float InValue);
	void ReturnHealth(float InTime);

	inline bool IsFullMovability() { return CurrentMovability == GetLevelInfo().Movability; }
	void SetCurrentMovability(float InValue);
	inline float GetCurrentMovability() const { return CurrentMovability; }
	void ReturnMovability(float InTime);
	void ConsumeMovability();

	inline bool IsFullAttackPower() { return CurrentAttackInterval == GetAttackInterval(); }
	inline float GetCurrentAttackInterval() const { return CurrentAttackInterval; }
	void ReturnAttackPower(float InTime);

	inline int32 GetMoveRange() const { return SoldierConfig.MoveRange; }
	inline int32 GetVisibleRange() const { return SoldierConfig.VisibleRange; }
	inline int32 GetAttackRange() const { return SoldierConfig.AttackRange; }
	inline float GetAttackInterval() const { return SoldierConfig.AttackInterval; }

protected:
	class ASoldierPawn * SoldierPawn;
	class CommandCenterDataClass * CommandCenter;

	FGuid   CommandCenterId;
	FString SoldierName;
	SoldierTypeEnum SoldierType;
	SoldierConfigStruct SoldierConfig;

	float CurrentHealth;
	float CurrentReturnHealthInterval;

	float CurrentMovability;
	float CurrentReturnMovabilityInterval;

	float CurrentAttackInterval;

	int32 CurrentLevel;

};
