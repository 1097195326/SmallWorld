using UnrealBuildTool;

public class ProceduralMesh : ModuleRules
{
    public ProceduralMesh(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "CoreUObject",
                "Engine",

            });

        PrivateDependencyModuleNames.AddRange(
            new string[] {
                "RenderCore",
                "RHI"
            });
    }
}