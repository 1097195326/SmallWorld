using UnrealBuildTool;

public class GameFrame : ModuleRules
{
    public GameFrame(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
                new string[]
                {
                    "GameFrame/Public/Data",
                    "GameFrame/Public/FrameCore",
                    "GameFrame/Public/GameMudule",
                    "GameFrame/Public/Pawn",
                    "GameFrame/Public/Projectile",
                    "GameFrame/Public/Templates",
                    "GameFrame/Public/Weapons",
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