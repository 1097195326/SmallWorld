using UnrealBuildTool;

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
                "GCore",
            });

        PrivateDependencyModuleNames.AddRange(
            new string[] {
                
            });
    }
}