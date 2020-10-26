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
	
	inline bool	IsMaxLevel() { return Level == SoldierConfig.maxlevel; }
	inline FString GetSoldierName() { return SoldierName; }
	inline const SoldierConfigStruct & GetSoldierConfig() { return SoldierConfig; }
	inline SoldierTypeEnum GetSoldierType() { return SoldierType; }
	inline int32 GetMovePower() const { return MovePower; }
	inline int32 GetMoveDistance() const { return SoldierConfig.distance; }
protected:
	class ASoldierPawn *		SoldierPawn;
	class CommandCenterDataClass * CommandCenter;

	FString					SoldierName;
	SoldierConfigStruct		SoldierConfig;
	SoldierTypeEnum			SoldierType;

	float	Health;
	int32	Level;
	int32	MovePower;

};
