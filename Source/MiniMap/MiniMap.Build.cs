using UnrealBuildTool;

public class MiniMap : ModuleRules
{
    public MiniMap(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "ApplicationCore",
                "AppFramework",
                "InputCore"
            });

        PrivateDependencyModuleNames.AddRange(
            new string[] {
                "RenderCore",
                "RHI",
            });
    }
}