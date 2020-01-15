#include "GameConfigData.h"


G_REGISTER_CLASS(GameConfigData)

const FString LocalLanguage = TEXT("zh");

TArray<FString> GameConfigData::NoCenterBuilding = { TEXT("CommandCenter") };
TArray<FString> GameConfigData::HaveCenterBuilding = { TEXT("ArmyCenter"),TEXT("Bakery"), TEXT("Farm"), TEXT("FoodStore"), TEXT("FruitFarm"), TEXT("Gate"), TEXT("House"), TEXT("Mill"), TEXT("MoneyStore"), TEXT("WoodStoneStore"), TEXT("ArmyCenter"), TEXT("Tower"), TEXT("Wall") };


void GameConfigData::InitWithXML(const FXmlFile * xmlFile)
{
	const FXmlNode * RootNode = xmlFile->GetRootNode();
	for (const FXmlNode * DataTypeInfo = RootNode->GetFirstChildNode(); DataTypeInfo != NULL; DataTypeInfo = DataTypeInfo->GetNextNode())
	{
		FString DataType = DataTypeInfo->GetAttribute(TEXT("type"));
		if (DataType.Equals(TEXT("BuildingsData")))
		{
			for (const FXmlNode * DataInfo = DataTypeInfo->GetFirstChildNode(); DataInfo != NULL; DataInfo = DataInfo->GetNextNode())
			{
				BuildingConfig config;
				config.name = DataInfo->GetAttribute(TEXT("name"));
				config.title = DataInfo->GetAttribute(TEXT("title"));
				config.describe = DataInfo->GetAttribute(TEXT("describe"));
				config.maxlevel = FCString::Atoi(*DataInfo->GetAttribute(TEXT("maxlevel"))) ;
				for (const FXmlNode * LevelInfo = DataInfo->GetFirstChildNode(); LevelInfo != NULL; LevelInfo = LevelInfo->GetNextNode())
				{
					BuildingLevelInfo info;
					info.level = FCString::Atoi(*LevelInfo->GetAttribute(TEXT("level")));
					info.upmoney = FCString::Atoi(*LevelInfo->GetAttribute(TEXT("upmoney")));
					info.upstone = FCString::Atoi(*LevelInfo->GetAttribute(TEXT("upstone")));
					info.upwood = FCString::Atoi(*LevelInfo->GetAttribute(TEXT("upwood")));
					info.factor = FCString::Atof(*LevelInfo->GetAttribute(TEXT("factor")));
					config.LevelInfos.Add(info);
				}
				BuildingConfigMap.Add(config.name, config);
			}
		}
		else if (DataType.Equals(TEXT("SoldiersData")))
		{

		}
		else if (DataType.Equals(TEXT("LanguageData")))
		{
			for (const FXmlNode * DataInfo = DataTypeInfo->GetFirstChildNode(); DataInfo != NULL; DataInfo = DataInfo->GetNextNode())
			{
				TMap<FString, FString> language;
				for (const FXmlNode * info = DataInfo->GetFirstChildNode(); info != NULL; info = info->GetNextNode())
				{
					language.Add(info->GetAttribute(TEXT("key")), info->GetAttribute(TEXT("value")));
				}
				LanguageMap.Add(DataInfo->GetAttribute(TEXT("name")), language);
			}
		}
	}
	for (auto & building : BuildingConfigMap)
	{
		building.Value.title = LanguageMap[LocalLanguage][building.Value.title];
		building.Value.describe = LanguageMap[LocalLanguage][building.Value.describe];
	}
	
}
const BuildingConfig & GameConfigData::GetBuildingConfig(FString name)
{
	return BuildingConfigMap[name];
}
TArray<BuildingConfig> GameConfigData::GetBuildingConfigs(const TArray<FString> & names)
{
	TArray<BuildingConfig> TemArray;
	for (auto name : names)
	{
		if (BuildingConfigMap.Contains(name))
		{
			TemArray.Add(BuildingConfigMap[name]);
		}
	}
	return MoveTemp(TemArray);
}
FString GameConfigData::TranslateLanguage(FString key)
{
	if (LanguageMap.Contains(LocalLanguage) && LanguageMap[LocalLanguage].Contains(key))
	{
		return LanguageMap[LocalLanguage][key];
	}
	return TEXT("");
}