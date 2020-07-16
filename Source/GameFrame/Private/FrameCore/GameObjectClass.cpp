//
//  GameObjectClass.cpp
//  GameFrame_Index
//
//  Created by fafa on 2018/8/9.
//  Copyright © 2018年 Epic Games, Inc. All rights reserved.
//
////#include "GCore.h"
#include "GameObjectClass.h"

GameObjectClass::GameObjectClass()
{
	//ObjectData = nullptr;
	GameData = nullptr;
}
GameObjectClass::~GameObjectClass()
{
	//ObjectData = nullptr;
	GameData = nullptr;

}
void GameObjectClass::On_Init(){}
void GameObjectClass::On_Start(){}
void GameObjectClass::On_Tick(float delta){}
void GameObjectClass::On_GameUpdate(){}
void GameObjectClass::On_End(){}
void GameObjectClass::On_Delete(){}
