#pragma once


#include "SingleTemplate.h"
#include "UserData.h"
#include "GameConfigData.h"


class DataManager : public SingleTemplate<DataManager>
{
public:
	void LoadData();
	
		

	UserData * GetUserData() { return mUserData; }
	GameConfigData * GetGameConfigData() { return mGameConfigData; }
private:
	void  LoadGameConfigData();

	UserData * mUserData;
	GameConfigData * mGameConfigData;

};
