#pragma once

#include "TemplateDataClass.h"

struct BuildingLevelInfoStruct 
{
	BuildingLevelInfoStruct(){}
	BuildingLevelInfoStruct(int32 temLevel) { level = temLevel; }
	int32 level;
	int32 upmoney;
	int32 upstone;
	int32 upwood;
	float factor;
	bool operator == (const BuildingLevelInfoStruct & info){return level == info.level;}
	bool operator != (const BuildingLevelInfoStruct & info){return level != info.level;}
};
struct BuildingConfigStruct
{
	FString name;
	FString title;
	FString describe;
	int32 maxlevel;
	TMap<int32,BuildingLevelInfoStruct> LevelInfos;
};
struct SoldierLevelInfoStruct
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
struct SoldierConfigStruct
{
	FString name;
	FString race;
	FString title;
	FString describe;
	int32 maxlevel;
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



