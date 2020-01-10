#include "GameConfigData.h"


G_REGISTER_CLASS(GameConfigData)

const FString LocalLanguage = TEXT("zh");

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
				if (DataInfo->GetAttribute(TEXT("name")).Equals(LocalLanguage))
				{
					for (const FXmlNode * info = DataInfo->GetFirstChildNode(); info != NULL; info = info->GetNextNode())
					{
						LanguageMap.Add(info->GetAttribute(TEXT("key")), info->GetAttribute(TEXT("value")));
					}
				}
			}
		}
	}

	for (auto & config : BuildingConfigMap)
	{
		config.Value.title = LanguageMap.Contains(config.Value.title) ? LanguageMap[config.Value.title] : config.Value.title;
		config.Value.describe = LanguageMap.Contains(config.Value.describe) ? LanguageMap[config.Value.describe] : config.Value.describe;
	}
	
}