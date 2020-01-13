#pragma once


#include "SingleTemplate.h"
#include "UserData.h"
#include "GameConfigData.h"
#include "GameWorldData.h"

class DataManager : public SingleTemplate<DataManager>
{
public:
	DataManager();

	void InitData();
	void LoadData();
	void ClearData();
		

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