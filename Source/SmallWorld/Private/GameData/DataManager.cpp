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
	mGameWorldData->InitUserData(mUserData);

}
void DataManager::LoadData()
{
	LoadUserData();
	LoadGameConfigData();
	LoadGameWorldData();

	if (!mUserData->GetHordeId().IsValid())
	{
		InitData();
		SaveData();
	}
}
void DataManager::SaveData()
{
	FString Content;
	auto writer = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&Content);
	mUserData->Serialization(writer);
	writer->Close();
	FFileHelper::SaveStringToFile(Content, *UserDataFilePath);

	Content.Empty();
	mGameWorldData->Serialization(writer);
	writer->Close();
	FFileHelper::SaveStringToFile(Content, *GameWorldDataFilePath);
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
	if (mUserData == nullptr)
	{
		mUserData = new UserData();
	}
	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*UserDataFilePath))
	{
		FString Content;
		FFileHelper::LoadFileToString(Content, *UserDataFilePath);
		auto fileReader = TJsonReaderFactory<TCHAR>::Create(Content);
		TSharedPtr<FJsonObject> JsonContent = MakeShareable(new FJsonObject);
		FJsonSerializer::Deserialize(fileReader, JsonContent);
		mUserData->Deserialization(JsonContent);
		return true;
	}
	return false;
}
void DataManager::LoadGameWorldData()
{
	if (mGameWorldData == nullptr)
	{
		mGameWorldData = new GameWorldData();
	}
	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*GameWorldDataFilePath))
	{
		FString Content;
		FFileHelper::LoadFileToString(Content, *GameWorldDataFilePath);
		auto fileReader = TJsonReaderFactory<TCHAR>::Create(Content);
		TSharedPtr<FJsonObject> JsonContent = MakeShareable(new FJsonObject);
		FJsonSerializer::Deserialize(fileReader, JsonContent);
		mGameWorldData->Deserialization(JsonContent);
	}
}