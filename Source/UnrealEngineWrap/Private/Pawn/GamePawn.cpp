//
//  GPawn.c
//  GameFrame_Index
//
//  Created by fafa on 2018/8/9.
//  Copyright © 2018年 Epic Games, Inc. All rights reserved.
//

//#include "GCore.h"
#include "GamePawn.h"

void AGamePawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	On_Init();
}
void AGamePawn::BeginPlay()
{
	Super::BeginPlay();
	On_Start();
}
void AGamePawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	On_Tick(DeltaSeconds);
}
void AGamePawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	On_End();
	Super::EndPlay(EndPlayReason);
}
void AGamePawn::BeginDestroy()
{
	On_Delete();
	Super::BeginDestroy();
}