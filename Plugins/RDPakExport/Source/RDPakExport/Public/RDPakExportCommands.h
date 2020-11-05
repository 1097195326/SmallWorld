// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "SlateBasics.h"
#include "RDPAKExportStyle.h"

class FRDPakExportCommands : public TCommands<FRDPakExportCommands>
{
public:

	FRDPakExportCommands()
		: TCommands<FRDPakExportCommands>(TEXT("RDPakExport"), NSLOCTEXT("Contexts", "RDPakExport", "RD PakExport Plugin"), NAME_None, FRDPakExportStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
