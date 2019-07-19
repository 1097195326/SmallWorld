//
//  GObject.hpp
//  GameFrame_Index
//
//  Created by fafa on 2018/8/9.
//  Copyright © 2018年 Epic Games, Inc. All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "ClassReflect.h"
#include <utility>

class GCORE_API GObject
{
private:
	FGuid	m_ID;
public:
    GObject();
    virtual ~GObject();

	virtual void On_Init();
	virtual void On_Start();
	virtual void On_Tick(float delta);
	virtual void On_GameUpdate();
	virtual void On_End();
	virtual void On_Delete();
public:

    FGuid GetID();
    
};

