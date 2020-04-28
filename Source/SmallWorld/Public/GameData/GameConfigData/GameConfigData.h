#pragma once

#include "DataT.h"

struct SBuildingLevelInfo 
{
	SBuildingLevelInfo(){}
	SBuildingLevelInfo(int32 temLevel) { level = temLevel; }
	int32 level;
	int32 upmoney;
	int32 upstone;
	int32 upwood;
	float factor;
	bool operator == (const SBuildingLevelInfo & info){return level == info.level;}
	bool operator != (const SBuildingLevelInfo & info){return level != info.level;}
};
struct SBuildingConfig
{
	FString name;
	FString title;
	FString describe;
	int32 maxlevel;
	TMap<int32,SBuildingLevelInfo> LevelInfos;
};
struct SSoldierLevelInfo
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
struct SSoldierConfig
{
	FString name;
	FString race;
	FString title;
	FString describe;
	int32 maxlevel;
	TMap<int32, SSoldierLevelInfo> LevelInfos;
};
class GameConfigData : public DataT
{
public:
	static TArray<FString> NoCenterBuilding;
	static TArray<FString> HaveCenterBuilding;
	static TArray<FString> SoldierNames;
	static FString SoldierPeasantName;

	virtual void InitWithXML(const FXmlFile * _file) override;

	
	TArray<SBuildingConfig> GetBuildingConfigs(const TArray<FString> &  names);
	const SBuildingConfig & GetBuildingConfig(FString name);
	TArray<SSoldierConfig> GetSoldierConfigs(const TArray<FString> &  names);
	const SSoldierConfig & GetSoldierConfig(FString name);

	FString TranslateLanguage(FString key);
private:

	TMap<FString, SSoldierConfig>  SoldierConfigMap;
	TMap<FString, SBuildingConfig>  BuildingConfigMap;
	TMap<FString,TMap<FString, FString>> LanguageMap;
};



