#include "DataManager.h"
#include "GamePath.h"


FString GameConfigDataFilePath = GamePath::GameConfigPath() + TEXT("GameConfigData.xml");
FString UserDataFilePath = GamePath::SaveAbsolutePath() + TEXT("UserData.json");
FString GameWorldDataFilePath = GamePath::SaveAbsolutePath() + TEXT("GameWorldData.json");


DataManager::DataManager()
{
	mUserData = nullptr;
	mGameConfigData = nullptr;
	mGameWorldData = nullptr;
}
void DataManager::InitData()
{
	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*UserDataFilePath))
	{

	}
	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*GameWorldDataFilePath))
	{

	}

}
void DataManager::LoadData()
{
	LoadUserData();
	LoadGameConfigData();
	LoadGameWorldData();

}
void DataManager::ClearData()
{
	delete mUserData;
	delete mGameConfigData;
	delete mGameWorldData;

	mUserData = nullptr;
	mGameConfigData = nullptr;
	mGameWorldData = nullptr;
}
void DataManager::LoadGameConfigData()
{
	 if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*GameConfigDataFilePath))
	 {
		 FXmlFile GameConfigFile(GameConfigDataFilePath);
		 FXmlNode * RootNode = GameConfigFile.GetRootNode();
		 FString ClassName = RootNode->GetAttribute(TEXT("classname"));
		 if (!ClassName.IsEmpty())
		 {
			 mGameConfigData = (GameConfigData*)(ReflectManager::Get()->GetClassByName(TCHAR_TO_UTF8(*ClassName)));
			 mGameConfigData->InitWithXML(&GameConfigFile);
		 }
	 }
}
bool DataManager::LoadUserData()
{
	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*UserDataFilePath))
	{

		return true;
	}
	return false;
}
void DataManager::LoadGameWorldData()
{

}