// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "IOSPack.h"


#define LOCTEXT_NAMESPACE "FIOSPack"

void FIOSPack::StartupModule()
{
	
}

void FIOSPack::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
}
#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FIOSPack, IOSPack)