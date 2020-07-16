#pragma once


#include "SingleTemplateClass.h"
#include "UserDataClass.h"
#include "GameConfigDataClass.h"
#include "GameWorldDataClass.h"


DECLARE_MULTICAST_DELEGATE(FFoodDataChangedDelegate);
DECLARE_MULTICAST_DELEGATE(FGoldDataChangedDelegate);
DECLARE_MULTICAST_DELEGATE(FWoodStoneDataChangedDelegate);
DECLARE_MULTICAST_DELEGATE(FPeopleDataChangedDelegate);


class GameDataManager : public SingleTemplateClass<GameDataManager>
{
public:
	GameDataManager();
	~GameDataManager();

	void InitData();
	void LoadData();
	void SaveData();
	void ClearData();
		
	FFoodDataChangedDelegate  FoodDataChangedDelegate;
	FGoldDataChangedDelegate  GoldDataChangedDelegate;
	FWoodStoneDataChangedDelegate  StoneDataChangedDelegate;
	FWoodStoneDataChangedDelegate  WoodDataChangedDelegate;
	FPeopleDataChangedDelegate  PeopleDataChangedDelegate;

	inline UserDataClass * GetUserData() { return mUserData; }
	inline GameConfigDataClass * GetGameConfigData() { return mGameConfigData; }
	inline GameWorldDataClass * GetGameWorldData() { return mGameWorldData; }

	FAssetData  GetBuildingAssetDataByIconName(FString MeshName);

private:
	void  LoadGameConfigData();
	bool  LoadUserData();
	void  LoadGameWorldData();

	UserDataClass * mUserData;
	GameConfigDataClass * mGameConfigData;
	GameWorldDataClass * mGameWorldData;
	TArray<FAssetData> BuildingAssetArray;
	TArray<ASoldierPawn*> SoldierAssetArray;

};

#define TransLanguage(key) \
(GameDataManager::GetInstance()->GetGameConfigData() != nullptr ? \
GameDataManager::GetInstance()->GetGameConfigData()->TranslateLanguage(key) :\
TEXT("") )