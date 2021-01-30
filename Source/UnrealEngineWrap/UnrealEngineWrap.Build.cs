using UnrealBuildTool;

public class UnrealEngineWrap : ModuleRules
{
    public UnrealEngineWrap(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[] {
                "UnrealEngineWrap/Public",
                "UnrealEngineWrap/Public/Actor",
                "UnrealEngineWrap/Public/Controller",
                "UnrealEngineWrap/Public/GameInterface",
                "UnrealEngineWrap/Public/Pawn",
                "UnrealEngineWrap/Public/UI",
            }
            );

        PublicDependencyModuleNames.AddRange(
            new string[] {

                "Core",
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "UMG",
                "GameFrame",

            });

        PrivateDependencyModuleNames.AddRange(
            new string[] {
                "RenderCore",
                "RHI",
            });
    }
}