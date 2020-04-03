#include "DataManager.h"
#include "GamePath.h"

#include "Modules/ModuleManager.h"
#include "AssetRegistryModule.h"
#include "Engine/StreamableManager.h"
#include "Engine/ObjectLibrary.h"


FString GameConfigDataFilePath = GamePath::GameConfigPath() + TEXT("GameConfigData.xml");
FString UserDataFilePath = GamePath::SaveAbsolutePath() + TEXT("UserData.json");
FString GameWorldDataFilePath = GamePath::SaveAbsolutePath() + TEXT("GameWorldData.json");


DataManager::DataManager()
{
	mUserData = nullptr;
	mGameConfigData = nullptr;
	mGameWorldData = nullptr;

	

}
DataManager::~DataManager()
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
	UObjectLibrary * BuildingAssetLibrary = UObjectLibrary::CreateLibrary(UObject::StaticClass(), false, false);
	BuildingAssetLibrary->LoadAssetDataFromPath(GamePath::BuildingAssetPath);
	BuildingAssetLibrary->GetAssetDataList(BuildingAssetArray);

	// load data
	LoadGameConfigData();
	LoadGameWorldData();
	LoadUserData();
	// Init Data
	InitData();

	
}
void DataManager::SaveData()
{
	FString Content;
	auto UserWriter = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&Content);

	UserWriter->WriteObjectStart();
	mUserData->Serialization(UserWriter);
	UserWriter->WriteObjectEnd();
	UserWriter->Close();
	FFileHelper::SaveStringToFile(Content, *UserDataFilePath);

	Content.Empty();
	auto WorldWriter = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&Content);
	WorldWriter->WriteObjectStart();
	mGameWorldData->Serialization(WorldWriter);
	WorldWriter->WriteObjectEnd();
	WorldWriter->Close();
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
		mUserData->Deserialization(JsonContent->GetObjectField("UserData"));


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
		mGameWorldData->Deserialization(JsonContent->GetObjectField("GameWorldData"));
	}
}
 FAssetData DataManager::GetBuildingAssetDataByIconName(FString MeshName)
{
	for (auto & assetData : BuildingAssetArray)
	{
		if (assetData.AssetName.ToString().Equals(MeshName))
		{
			return assetData;
		}
	}
	return NULL;
}