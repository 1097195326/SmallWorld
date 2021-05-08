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
void GameConfigDataClass::ClearData()
{
	if (ResourceTable)
	{
		ResourceTable->RemoveFromRoot();
		ResourceTable = nullptr;
	}
}
void GameConfigDataClass::LoadGameDataTables()
{
	 ResourceTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Configs/ResourceTable.ResourceTable"));
	 ResourceTable->AddToRoot();
}
void GameConfigDataClass::InitWithXML(const FXmlFile * xmlFile)
{
	const FXmlNode * RootNode = xmlFile->GetRootNode();
	for (const FXmlNode * DataTypeInfo = RootNode->GetFirstChildNode(); DataTypeInfo != NULL; DataTypeInfo = DataTypeInfo->GetNextNode())
	{
		FString DataType = DataTypeInfo->GetAttribute(TEXT("Type"));
		if (DataType.Equals(TEXT("BuildingsData")))
		{
			for (const FXmlNode * DataInfo = DataTypeInfo->GetFirstChildNode(); DataInfo != NULL; DataInfo = DataInfo->GetNextNode())
			{
				BuildingConfigStruct config;
				config.Name = DataInfo->GetAttribute(TEXT("Name"));
				config.Title = DataInfo->GetAttribute(TEXT("Title"));
				config.Describe = DataInfo->GetAttribute(TEXT("Describe"));
				config.MaxLevel = FCString::Atoi(*DataInfo->GetAttribute(TEXT("MaxLevel"))) ;
				for (const FXmlNode * LevelInfo = DataInfo->GetFirstChildNode(); LevelInfo != NULL; LevelInfo = LevelInfo->GetNextNode())
				{
					BuildingLevelInfoStruct info;
					info.Level = FCString::Atoi(*LevelInfo->GetAttribute(TEXT("Level")));
					info.UpdateInterval = FCString::Atoi(*LevelInfo->GetAttribute(TEXT("UpdateInterval")));
					info.UpMoney = FCString::Atoi(*LevelInfo->GetAttribute(TEXT("UpMoney")));
					info.UpStone = FCString::Atoi(*LevelInfo->GetAttribute(TEXT("UpStone")));
					info.UpWood = FCString::Atoi(*LevelInfo->GetAttribute(TEXT("UpWood")));
					info.Factor = FCString::Atof(*LevelInfo->GetAttribute(TEXT("Factor")));
					config.LevelInfos.Add(info.Level,info);
				}
				BuildingConfigMap.Add(config.Name, config);
			}
		}
		else if (DataType.Equals(TEXT("SoldiersData")))
		{
			for (const FXmlNode * DataInfo = DataTypeInfo->GetFirstChildNode(); DataInfo != NULL; DataInfo = DataInfo->GetNextNode())
			{
				SoldierConfigStruct config;
				config.Name = DataInfo->GetAttribute(TEXT("Name"));
				config.Race = DataInfo->GetAttribute(TEXT("Race"));
				config.Title = DataInfo->GetAttribute(TEXT("Title"));
				config.Describe = DataInfo->GetAttribute(TEXT("Describe"));
				config.MaxLevel = FCString::Atoi(*DataInfo->GetAttribute(TEXT("MaxLevel")));
				config.MoveRange = FCString::Atoi(*DataInfo->GetAttribute("MoveRange"));
				config.VisibleRange = FCString::Atoi(*DataInfo->GetAttribute("VisibleRange"));

				for (const FXmlNode * LevelInfo = DataInfo->GetFirstChildNode(); LevelInfo != NULL; LevelInfo = LevelInfo->GetNextNode())
				{
					SoldierLevelInfoStruct info;
					info.Level = FCString::Atoi(*LevelInfo->GetAttribute(TEXT("Level")));
					info.NeedExperience = FCString::Atoi(*LevelInfo->GetAttribute(TEXT("NeedExperience")));
					info.ProvideExperience = FCString::Atoi(*LevelInfo->GetAttribute(TEXT("ProvideExperience")));
					info.Health = FCString::Atoi(*LevelInfo->GetAttribute(TEXT("Health")));
					info.HealthReturnInterval = FCString::Atoi(*LevelInfo->GetAttribute(TEXT("HealthReturnInterval")));
					info.HealthReturnSpeed = FCString::Atoi(*LevelInfo->GetAttribute(TEXT("HealthReturnSpeed")));
					info.Movability = FCString::Atoi(*LevelInfo->GetAttribute(TEXT("Movability")));
					info.MovabilityReturnInterval = FCString::Atoi(*LevelInfo->GetAttribute(TEXT("MovabilityReturnInterval")));
					info.MovabilityReturnSpeed = FCString::Atoi(*LevelInfo->GetAttribute(TEXT("MovabilityReturnSpeed")));
					info.MoveConsume = FCString::Atoi(*LevelInfo->GetAttribute(TEXT("MoveConsume")));
					info.PhyDamage = FCString::Atof(*LevelInfo->GetAttribute(TEXT("PhyDamage")));
					info.MagicDamage = FCString::Atof(*LevelInfo->GetAttribute(TEXT("MagicDamage")));
					info.PhyDef = FCString::Atof(*LevelInfo->GetAttribute(TEXT("PhyDef")));
					info.MagDef = FCString::Atof(*LevelInfo->GetAttribute(TEXT("MagDef")));
					info.Factor = FCString::Atof(*LevelInfo->GetAttribute(TEXT("Factor")));
					config.LevelInfos.Add(info.Level, info);
				}
				SoldierConfigMap.Add(config.Name, config);
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
		building.Value.Title = LanguageMap[LocalLanguage][building.Value.Title];
		building.Value.Describe = LanguageMap[LocalLanguage][building.Value.Describe];
	}
	for (auto & soldier : SoldierConfigMap)
	{
		soldier.Value.Title = LanguageMap[LocalLanguage][soldier.Value.Title];
		soldier.Value.Describe = LanguageMap[LocalLanguage][soldier.Value.Describe];
	}

}
const FResourceTableRow * GameConfigDataClass::GetResourceTableRowByName(FString InName)
{
	if (ResourceTable)
	{
		return ResourceTable->FindRow<FResourceTableRow>(FName(InName), TEXT(""));
	}
	return nullptr;
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