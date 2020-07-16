//
//  GameObjectClass.hpp
//  GameFrame_Index
//
//  Created by fafa on 2018/8/9.
//  Copyright © 2018年 Epic Games, Inc. All rights reserved.
//

#pragma once

#include "BaseObjectClass.h"
#include "GameDataClass.h"

class GAMEFRAME_API GameObjectClass : public BaseObjectClass
{


public:
	GameObjectClass();
	~GameObjectClass();
	
	virtual void On_Init();
	virtual void On_Start();
	virtual void On_Tick(float DeltaSeconds);
	virtual void On_GameUpdate();
	virtual void On_End();
	virtual void On_Delete();
public:
	void	SetGameData(void * InData) { GameData = InData; }
	template<typename T>
	T *	GetGameData() { return dynamic_cast<T*>(GameData); }
	void *	GetGameData() { return GameData; }
	//inline GameDataClass * GetObjectData() { return ObjectData; }
protected:
	//GameDataClass * ObjectData;
	void *  GameData;
    
};

