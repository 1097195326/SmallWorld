// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DownloadTool : ModuleRules
{
	public DownloadTool(ReadOnlyTargetRules Target) : base(Target)
	{
        //PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        PrivatePCHHeaderFile = "Public/DownloadTool.h";

        PublicIncludePaths.AddRange(
			new string[] {

            //"Share/Public/Sharing",

            }
            );
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
                //"Share/Private/Sharing",
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
                "Core", "CoreUObject", "Engine", "InputCore","Http" ,"ImageDownload"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
                
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
