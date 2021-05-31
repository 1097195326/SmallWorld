//
//  GPawn.c
//  GameFrame_Index
//
//  Created by fafa on 2018/8/9.
//  Copyright © 2018年 Epic Games, Inc. All rights reserved.
//

//#include "GCore.h"
#include "WrapPawn.h"

void AWrapPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	On_Init();
}
void AWrapPawn::BeginPlay()
{
	Super::BeginPlay();
	On_Start();
}
void AWrapPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	On_Tick(DeltaSeconds);
}
void AWrapPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	On_End();
	Super::EndPlay(EndPlayReason);
}
void AWrapPawn::BeginDestroy()
{
	On_Delete();
	Super::BeginDestroy();
}