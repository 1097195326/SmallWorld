#include "DataManager.h"
#include "GamePath.h"


void DataManager::LoadData()
{
	LoadGameConfigData();

}
void DataManager::LoadGameConfigData()
{
	 FString FilePath = GamePath::GameConfigPath() + TEXT("GameConfigData.xml");
	
	 if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath))
	 {
		 FXmlFile GameConfigFile(FilePath);
		 FXmlNode * RootNode = GameConfigFile.GetRootNode();
		 FString ClassName = RootNode->GetAttribute(TEXT("classname"));
		 if (!ClassName.IsEmpty())
		 {
			  GData * Data = (GData*)(ReflectManager::Get()->GetClassByName(TCHAR_TO_UTF8(*ClassName)));
			  Data->InitWithXML(&GameConfigFile);
		 }
	 }
}