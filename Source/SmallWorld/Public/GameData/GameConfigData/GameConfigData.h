#pragma once

#include "DataT.h"

struct BuildingLevelInfo 
{
	BuildingLevelInfo(){}
	BuildingLevelInfo(int32 temLevel) { level = temLevel; }
	int32 level;
	int32 upmoney;
	int32 upstone;
	int32 upwood;
	float factor;
	bool operator == (const BuildingLevelInfo & info){return level == info.level;}
	bool operator != (const BuildingLevelInfo & info){return level != info.level;}
};
struct BuildingConfig
{
	FString name;
	FString title;
	FString describe;
	int32 maxlevel;
	TMap<int32,BuildingLevelInfo> LevelInfos;
};
struct SoldierLevelInfo
{
	int32 level;
	int32 health;
	int32 kills;
	float phydamage;
	float magicdamage;
	float phydef;
	float magdef;
	float factor;
};
struct SoldierConfig
{
	FString name;
	FString race;
	FString title;
	FString describe;
	int32 maxlevel;
	TMap<int32, SoldierLevelInfo> LevelInfos;
};
class GameConfigData : public DataT
{
public:
	static TArray<FString> NoCenterBuilding;
	static TArray<FString> HaveCenterBuilding;
	static TArray<FString> SoldierNames;

	virtual void InitWithXML(const FXmlFile * _file) override;

	
	TArray<BuildingConfig> GetBuildingConfigs(const TArray<FString> &  names);
	const BuildingConfig & GetBuildingConfig(FString name);
	TArray<SoldierConfig> GetSoldierConfigs(const TArray<FString> &  names);
	const SoldierConfig & GetSoldierConfig(FString name);

	FString TranslateLanguage(FString key);
private:

	TMap<FString, SoldierConfig>  SoldierConfigMap;
	TMap<FString, BuildingConfig>  BuildingConfigMap;
	TMap<FString,TMap<FString, FString>> LanguageMap;
};



