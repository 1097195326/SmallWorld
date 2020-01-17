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

class GameConfigData : public DataT
{
public:
	static TArray<FString> NoCenterBuilding;
	static TArray<FString> HaveCenterBuilding;

	virtual void InitWithXML(const FXmlFile * _file) override;

	
	TArray<BuildingConfig> GetBuildingConfigs(const TArray<FString> &  names);
	const BuildingConfig & GetBuildingConfig(FString name);
	FString TranslateLanguage(FString key);
private:

	TMap<FString, BuildingConfig>  BuildingConfigMap;
	TMap<FString,TMap<FString, FString>> LanguageMap;
};



