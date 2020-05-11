//
//  GObject.hpp
//  GameFrame_Index
//
//  Created by fafa on 2018/8/9.
//  Copyright © 2018年 Epic Games, Inc. All rights reserved.
//

#pragma once

#include "BaseObject.h"
#include "GData.h"

class GAMEFRAME_API GObject : public BaseObject
{


public:
	GObject();
	~GObject();
	
	virtual void On_Init();
	virtual void On_Start();
	virtual void On_Tick(float delta);
	virtual void On_GameUpdate();
	virtual void On_End();
	virtual void On_Delete();
public:
	void	SetGameData(void * InData) { GameData = InData; }
	template<typename T>
	T *	GetGameData() { return dynamic_cast<T*>(GameData); }
	void *	GetGameData() { return GameData; }
	//inline GData * GetObjectData() { return ObjectData; }
protected:
	//GData * ObjectData;
	void *  GameData;
    
};

