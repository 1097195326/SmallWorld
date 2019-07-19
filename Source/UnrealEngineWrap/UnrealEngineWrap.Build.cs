﻿using UnrealBuildTool;

public class UnrealEngineWrap : ModuleRules
{
    public UnrealEngineWrap(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[] {

                "Core",
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "UMG",
                "GCore",

            });

        PrivateDependencyModuleNames.AddRange(
            new string[] {
                "RenderCore",
                "RHI",
            });
    }
}