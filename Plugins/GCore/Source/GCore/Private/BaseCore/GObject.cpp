//
//  GObject.cpp
//  GameFrame_Index
//
//  Created by fafa on 2018/8/9.
//  Copyright © 2018年 Epic Games, Inc. All rights reserved.
//
////#include "GCore.h"
#include "GObject.h"

GObject::GObject()
{
	FPlatformMisc::CreateGuid(m_ID);

}
GObject::~GObject()
{
	On_Delete();
}
void GObject::On_Init(){}
void GObject::On_Start(){}
void GObject::On_Tick(float delta){}
void GObject::On_GameUpdate(){}
void GObject::On_End(){}
void GObject::On_Delete(){}
FGuid GObject::GetID()
{
    return m_ID;
}
