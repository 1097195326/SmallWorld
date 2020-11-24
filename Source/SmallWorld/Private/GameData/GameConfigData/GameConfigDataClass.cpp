#include "GameConfigDataClass.h"


G_REGISTER_CLASS(GameConfigDataClass)

const FString LocalLanguage = TEXT("zh");

TArray<FString> GameConfigDataClass::NoCenterBuilding = { TEXT("CommandCenter") };
TArray<FString> GameConfigDataClass::HaveCenterBuilding = 
{ 
	TEXT("ArmyCenter"),
	TEXT("Bakery"), 
	TEXT("Farm"),
	TEXT("FoodStore"),
	TEXT("FruitFarm"),
	TEXT("Gate"), 
	TEXT("House"),
	TEXT("Mill"),
	TEXT("MoneyStore"),
	TEXT("WoodStoneStore"),
	TEXT("ArmyCenter"),
	TEXT("Tower"),
	TEXT("Wall") 
};
FString GameConfigDataClass::SoldierPeasantName = TEXT("Peasant");
TArray<FString> GameConfigDataClass::SoldierNames = 
{ 
	TEXT("Archer"),
	TEXT("Footman"), 
	TEXT("Griffin"),
	TEXT("Horseman"),
	TEXT("Knight"),
	TEXT("Mage"),
	TEXT("SiegeEngine") 
};


void GameConfigDataClass::InitWithXML(const FXmlFile * xmlFile)
{
	const FXmlNode * RootNode = xmlFile->GetRootNode();
	for (const FXmlNode * DataTypeInfo = RootNode->GetFirstChildNode(); DataTypeInfo != NULL; DataTypeInfo = DataTypeInfo->GetNextNode())
	{
		FString DataType = DataTypeInfo->GetAttribute(TEXT("type"));
		if (DataType.Equals(TEXT("BuildingsData")))
		{
			for (const FXmlNode * DataInfo = DataTypeInfo->GetFirstChildNode(); DataInfo != NULL; DataInfo = DataInfo->GetNextNode())
			{
				BuildingConfigStruct config;
				config.name = DataInfo->GetAttribute(TEXT("name"));
				config.title = DataInfo->GetAttribute(TEXT("title"));
				config.describe = DataInfo->GetAttribute(TEXT("describe"));
				config.MaxLevel = FCString::Atoi(*DataInfo->GetAttribute(TEXT("maxlevel"))) ;
				for (const FXmlNode * LevelInfo = DataInfo->GetFirstChildNode(); LevelInfo != NULL; LevelInfo = LevelInfo->GetNextNode())
				{
					BuildingLevelInfoStruct info;
					info.level = FCString::Atoi(*LevelInfo->GetAttribute(TEXT("level")));
					info.upmoney = FCString::Atoi(*LevelInfo->GetAttribute(TEXT("upmoney")));
					info.upstone = FCString::Atoi(*LevelInfo->GetAttribute(TEXT("upstone")));
					info.upwood = FCString::Atoi(*LevelInfo->GetAttribute(TEXT("upwood")));
					info.factor = FCString::Atof(*LevelInfo->GetAttribute(TEXT("factor")));
					config.LevelInfos.Add(info.level,info);
				}
				BuildingConfigMap.Add(config.name, config);
			}
		}
		else if (DataType.Equals(TEXT("SoldiersData")))
		{
			for (const FXmlNode * DataInfo = DataTypeInfo->GetFirstChildNode(); DataInfo != NULL; DataInfo = DataInfo->GetNextNode())
			{
				SoldierConfigStruct config;
				config.name = DataInfo->GetAttribute(TEXT("name"));
				config.race = DataInfo->GetAttribute(TEXT("race"));
				config.title = DataInfo->GetAttribute(TEXT("title"));
				config.describe = DataInfo->GetAttribute(TEXT("describe"));
				config.maxlevel = FCString::Atoi(*DataInfo->GetAttribute(TEXT("maxlevel")));
				config.movability = FCString::Atoi(*DataInfo->GetAttribute("movability"));
				config.visibility = FCString::Atoi(*DataInfo->GetAttribute("visibility"));
				config.attackrange = FCString::Atoi(*DataInfo->GetAttribute("attackrange"));
				config.attackspeed = FCString::Atof(*DataInfo->GetAttribute("attackspeed"));

				for (const FXmlNode * LevelInfo = DataInfo->GetFirstChildNode(); LevelInfo != NULL; LevelInfo = LevelInfo->GetNextNode())
				{
					SoldierLevelInfoStruct info;
					info.level = FCString::Atoi(*LevelInfo->GetAttribute(TEXT("level")));
					info.health = FCString::Atoi(*LevelInfo->GetAttribute(TEXT("health")));
					info.kills = FCString::Atoi(*LevelInfo->GetAttribute(TEXT("kills")));
					info.restorehealth = FCString::Atof(*LevelInfo->GetAttribute(TEXT("restorehealth")));
					info.restoremovability = FCString::Atof(*LevelInfo->GetAttribute(TEXT("restoremovability")));
					info.phydamage = FCString::Atof(*LevelInfo->GetAttribute(TEXT("phydamage")));
					info.magicdamage = FCString::Atof(*LevelInfo->GetAttribute(TEXT("magicdamage")));
					info.phydef = FCString::Atof(*LevelInfo->GetAttribute(TEXT("phydef")));
					info.magdef = FCString::Atof(*LevelInfo->GetAttribute(TEXT("magdef")));
					info.factor = FCString::Atof(*LevelInfo->GetAttribute(TEXT("factor")));
					config.LevelInfos.Add(info.level, info);
				}
				SoldierConfigMap.Add(config.name, config);
			}
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
	for (auto & soldier : SoldierConfigMap)
	{
		soldier.Value.title = LanguageMap[LocalLanguage][soldier.Value.title];
		soldier.Value.describe = LanguageMap[LocalLanguage][soldier.Value.describe];
	}

}
const SoldierConfigStruct & GameConfigDataClass::GetSoldierConfig(FString name)
{
	return SoldierConfigMap[name];
}
TArray<SoldierConfigStruct> GameConfigDataClass::GetSoldierConfigs(const TArray<FString> & names)
{
	TArray<SoldierConfigStruct> TemArray;
	for (auto name : names)
	{
		if (SoldierConfigMap.Contains(name))
		{
			TemArray.Add(SoldierConfigMap[name]);
		}
	}
	return MoveTemp(TemArray);
}
const BuildingConfigStruct & GameConfigDataClass::GetBuildingConfig(FString name)
{
	return BuildingConfigMap[name];
}
TArray<BuildingConfigStruct> GameConfigDataClass::GetBuildingConfigs(const TArray<FString> & names)
{
	TArray<BuildingConfigStruct> TemArray;
	for (auto name : names)
	{
		if (BuildingConfigMap.Contains(name))
		{
			TemArray.Add(BuildingConfigMap[name]);
		}
	}
	return MoveTemp(TemArray);
}
FString GameConfigDataClass::TranslateLanguage(FString key)
{
	if (LanguageMap.Contains(LocalLanguage) && LanguageMap[LocalLanguage].Contains(key))
	{
		return LanguageMap[LocalLanguage][key];
	}
	return TEXT("");
}