// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "RDPakExportCommands.h"

#define LOCTEXT_NAMESPACE "FRDPakExportModule"

void FRDPakExportCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "导出Pak", "选择资源文件导出成pak", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
