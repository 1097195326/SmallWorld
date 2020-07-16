#include "GameDataManager.h"
#include "GamePath.h"

#include "Modules/ModuleManager.h"
#include "AssetRegistryModule.h"
#include "Engine/StreamableManager.h"
#include "Engine/ObjectLibrary.h"


FString GameConfigDataFilePath = GamePath::GameConfigPath() + TEXT("GameConfigDataClass.xml");
FString UserDataFilePath = GamePath::SaveAbsolutePath() + TEXT("UserDataClass.json");
FString GameWorldDataFilePath = GamePath::SaveAbsolutePath() + TEXT("GameWorldDataClass.json");


GameDataManager::GameDataManager()
{
	mUserData = nullptr;
	mGameConfigData = nullptr;
	mGameWorldData = nullptr;

	

}
GameDataManager::~GameDataManager()
{
	
	mUserData = nullptr;
	mGameConfigData = nullptr;
	mGameWorldData = nullptr;
}
void GameDataManager::InitData()
{
	
	mGameWorldData->InitUserData(mUserData);

}
void GameDataManager::LoadData()
{
	UObjectLibrary * AssetLibrary = UObjectLibrary::CreateLibrary(UObject::StaticClass(), true, false);
	AssetLibrary->LoadAssetDataFromPath(GamePath::BuildingAssetPath);
	AssetLibrary->GetAssetDataList(BuildingAssetArray);
	AssetLibrary->LoadBlueprintsFromPath(GamePath::SoldierAssetPath);
	AssetLibrary->GetObjects(SoldierAssetArray);

	// load data
	LoadGameConfigData();
	LoadGameWorldData();
	bool UserDataIsOk = LoadUserData();
	// Init Data
	InitData();

	
	if (!UserDataIsOk)
	{
		// User Data First Save
		SaveData();
	}
	
}
void GameDataManager::SaveData()
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
void GameDataManager::ClearData()
{
	delete mUserData;
	delete mGameConfigData;
	delete mGameWorldData;

	mUserData = nullptr;
	mGameConfigData = nullptr;
	mGameWorldData = nullptr;
}
void GameDataManager::LoadGameConfigData()
{
	 if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*GameConfigDataFilePath))
	 {
		 FXmlFile GameConfigFile(GameConfigDataFilePath);
		 FXmlNode * RootNode = GameConfigFile.GetRootNode();
		 FString ClassName = RootNode->GetAttribute(TEXT("classname"));
		 if (!ClassName.IsEmpty())
		 {
			 mGameConfigData = (GameConfigDataClass*)(ClassReflectManager::Get()->GetClassByName(TCHAR_TO_UTF8(*ClassName)));
			 mGameConfigData->InitWithXML(&GameConfigFile);
		 }
	 }
}
bool GameDataManager::LoadUserData()
{
	if (mUserData == nullptr)
	{
		mUserData = new UserDataClass();
	}
	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*UserDataFilePath))
	{
		FString Content;
		FFileHelper::LoadFileToString(Content, *UserDataFilePath);
		auto fileReader = TJsonReaderFactory<TCHAR>::Create(Content);
		TSharedPtr<FJsonObject> JsonContent = MakeShareable(new FJsonObject);
		FJsonSerializer::Deserialize(fileReader, JsonContent);
		mUserData->Deserialization(JsonContent->GetObjectField("UserDataClass"));


		return true;
	}
	return false;
}
void GameDataManager::LoadGameWorldData()
{
	if (mGameWorldData == nullptr)
	{
		mGameWorldData = new GameWorldDataClass();
	}
	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*GameWorldDataFilePath))
	{
		FString Content;
		FFileHelper::LoadFileToString(Content, *GameWorldDataFilePath);
		auto fileReader = TJsonReaderFactory<TCHAR>::Create(Content);
		TSharedPtr<FJsonObject> JsonContent = MakeShareable(new FJsonObject);
		FJsonSerializer::Deserialize(fileReader, JsonContent);
		mGameWorldData->Deserialization(JsonContent->GetObjectField("GameWorldDataClass"));
	}
}
 FAssetData GameDataManager::GetBuildingAssetDataByIconName(FString MeshName)
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