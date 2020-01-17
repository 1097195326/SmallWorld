#pragma once


#include "SingleTemplate.h"
#include "UserData.h"
#include "GameConfigData.h"
#include "GameWorldData.h"


DECLARE_MULTICAST_DELEGATE(FFoodDataChangedDelegate);
DECLARE_MULTICAST_DELEGATE(FGoldDataChangedDelegate);
DECLARE_MULTICAST_DELEGATE(FWoodStoneDataChangedDelegate);
DECLARE_MULTICAST_DELEGATE(FPeopleDataChangedDelegate);


class DataManager : public SingleTemplate<DataManager>
{
public:
	DataManager();

	void InitData();
	void LoadData();
	void SaveData();
	void ClearData();
		
	FFoodDataChangedDelegate  FoodDataChangedDelegate;
	FGoldDataChangedDelegate  GoldDataChangedDelegate;
	FWoodStoneDataChangedDelegate  StoneDataChangedDelegate;
	FWoodStoneDataChangedDelegate  WoodDataChangedDelegate;
	FPeopleDataChangedDelegate  PeopleDataChangedDelegate;

	UserData * GetUserData() { return mUserData; }
	GameConfigData * GetGameConfigData() { return mGameConfigData; }
private:
	void  LoadGameConfigData();
	bool  LoadUserData();
	void  LoadGameWorldData();

	UserData * mUserData;
	GameConfigData * mGameConfigData;
	GameWorldData * mGameWorldData;

};

#define TranslateL(key) \
DataManager::GetInstance()->GetGameConfigData() != nullptr ? \
DataManager::GetInstance()->GetGameConfigData()->TranslateLanguage(key) :\
TEXT("")