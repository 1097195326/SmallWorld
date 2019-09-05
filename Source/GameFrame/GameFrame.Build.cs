﻿using UnrealBuildTool;

public class GameFrame : ModuleRules
{
    public GameFrame(ReadOnlyTargetRules Target) : base(Target)
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
                "InputCore",
                "JsonUtilities",
                "Json",
                "HTTP",
                "Networking",
                "XmlParser",
                "GCore",
            });

        PrivateDependencyModuleNames.AddRange(
            new string[] {
                
            });
    }
}