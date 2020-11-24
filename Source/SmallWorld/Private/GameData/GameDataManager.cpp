#include "GameDataManager.h"
#include "GamePath.h"

#include "Modules/ModuleManager.h"
#include "AssetRegistryModule.h"
#include "Engine/StreamableManager.h"
#include "Engine/ObjectLibrary.h"


FString GameConfigDataFilePath = GamePath::GameConfigPath() + TEXT("GameConfigData.xml");
FString UserDataFilePath = GamePath::SaveAbsolutePath() + TEXT("UserData.json");
FString GameWorldDataFilePath = GamePath::SaveAbsolutePath() + TEXT("GameWorldData.json");


GameDataManager::GameDataManager()
{
	UserData = nullptr;
	GameConfigData = nullptr;
	GameWorldData = nullptr;

	

}
GameDataManager::~GameDataManager()
{
	
	UserData = nullptr;
	GameConfigData = nullptr;
	GameWorldData = nullptr;
}
void GameDataManager::InitData()
{
	GameWorldData->InitWorldData();
	GameWorldData->InitUserData(UserData);

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
	UserData->Serialization(UserWriter);
	UserWriter->WriteObjectEnd();
	UserWriter->Close();
	FFileHelper::SaveStringToFile(Content, *UserDataFilePath);

	Content.Empty();
	auto WorldWriter = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&Content);
	WorldWriter->WriteObjectStart();
	GameWorldData->Serialization(WorldWriter);
	WorldWriter->WriteObjectEnd();
	WorldWriter->Close();
	FFileHelper::SaveStringToFile(Content, *GameWorldDataFilePath);
}
void GameDataManager::ClearData()
{
	delete UserData;
	delete GameConfigData;
	delete GameWorldData;

	UserData = nullptr;
	GameConfigData = nullptr;
	GameWorldData = nullptr;
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
			 GameConfigData = (GameConfigDataClass*)(ClassReflectManager::Get()->GetClassByName(TCHAR_TO_UTF8(*ClassName)));
			 GameConfigData->InitWithXML(&GameConfigFile);
		 }
	 }
}
bool GameDataManager::LoadUserData()
{
	if (UserData == nullptr)
	{
		UserData = new UserDataClass();
	}
	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*UserDataFilePath))
	{
		FString Content;
		FFileHelper::LoadFileToString(Content, *UserDataFilePath);
		auto fileReader = TJsonReaderFactory<TCHAR>::Create(Content);
		TSharedPtr<FJsonObject> JsonContent = MakeShareable(new FJsonObject);
		FJsonSerializer::Deserialize(fileReader, JsonContent);
		UserData->Deserialization(JsonContent->GetObjectField("UserDataClass"));


		return true;
	}
	return false;
}
void GameDataManager::LoadGameWorldData()
{
	if (GameWorldData == nullptr)
	{
		GameWorldData = new GameWorldDataClass();
	}
	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*GameWorldDataFilePath))
	{
		FString Content;
		FFileHelper::LoadFileToString(Content, *GameWorldDataFilePath);
		auto fileReader = TJsonReaderFactory<TCHAR>::Create(Content);
		TSharedPtr<FJsonObject> JsonContent = MakeShareable(new FJsonObject);
		FJsonSerializer::Deserialize(fileReader, JsonContent);
		GameWorldData->Deserialization(JsonContent->GetObjectField("GameWorldDataClass"));
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
bool GameDataManager::IsUserHordeData(HordeDataClass * InHordeData)
{
	return GetUserData()->GetHordeData() == InHordeData;
}
bool GameDataManager::IsInUserHordeData(BaseBuildingDataClass * InBuilding)
{
	return GetUserData()->GetHordeData()->IsContains(InBuilding);
}
