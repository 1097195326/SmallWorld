#pragma once

#include "TemplateDataClass.h"

struct BuildingLevelInfoStruct 
{
	BuildingLevelInfoStruct(){}
	BuildingLevelInfoStruct(int32 temLevel) { Level = temLevel; }
	int32 Level;
	int32 UpdateInterval;
	int32 UpMoney;
	int32 UpStone;
	int32 UpWood;
	float Factor;
	bool operator == (const BuildingLevelInfoStruct & info){return Level == info.Level;}
	bool operator != (const BuildingLevelInfoStruct & info){return Level != info.Level;}
};
struct BuildingConfigStruct
{
	FString Name;
	FString Title;
	FString Describe;
	int32 MaxLevel;
	TMap<int32,BuildingLevelInfoStruct> LevelInfos;
};
struct SoldierLevelInfoStruct
{
	int32 Level;
	int32 NeedExperience;
	int32 ProvideExperience;
	int32 Health;
	int32 HealthReturnInterval;
	int32 HealthReturnSpeed;
	int32 Movability;
	int32 MovabilityReturnInterval;
	int32 MovabilityReturnSpeed;
	int32 MoveConsume;

	float PhyDamage;
	float MagicDamage;
	float PhyDef;
	float MagDef;
	float Factor;
};
struct SoldierConfigStruct
{
	FString Name = TEXT("");
	FString Race = TEXT("");
	FString Title = TEXT("");
	FString Describe =TEXT("");
	int32 MaxLevel = 1;
	int32 MoveRange = 1;
	int32 VisibleRange = 1;
	int32 AttackRange = 1;
	float AttackInterval = 1;
	TMap<int32, SoldierLevelInfoStruct> LevelInfos;
};
class GameConfigDataClass : public TemplateDataClass
{
public:
	static TArray<FString> NoCenterBuilding;
	static TArray<FString> HaveCenterBuilding;
	static TArray<FString> SoldierNames;
	static FString SoldierPeasantName;

	virtual void InitWithXML(const FXmlFile * _file) override;

	
	TArray<BuildingConfigStruct> GetBuildingConfigs(const TArray<FString> &  names);
	const BuildingConfigStruct & GetBuildingConfig(FString name);
	TArray<SoldierConfigStruct> GetSoldierConfigs(const TArray<FString> &  names);
	const SoldierConfigStruct & GetSoldierConfig(FString name);

	FString TranslateLanguage(FString key);
private:

	TMap<FString, SoldierConfigStruct>  SoldierConfigMap;
	TMap<FString, BuildingConfigStruct>  BuildingConfigMap;
	TMap<FString,TMap<FString, FString>> LanguageMap;
};



