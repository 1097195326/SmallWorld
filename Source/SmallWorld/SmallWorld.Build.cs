// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class SmallWorld : ModuleRules
{
	public SmallWorld(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
           new string[] {
               "SmallWorld",
                "SmallWorld/Public",
                "SmallWorld/Public/BehaviorTree",
                "SmallWorld/Public/DamageType",
                "SmallWorld/Public/Formation",
                "SmallWorld/Public/GameActors",
                "SmallWorld/Public/GameActors/BuildingActors",
                "SmallWorld/Public/GameActors/InteractionalActors",
                "SmallWorld/Public/GameActors/Projectile",
                "SmallWorld/Public/GameActors/Soldiers",
                "SmallWorld/Public/GameActors/Soldiers/SoldierState",
                "SmallWorld/Public/GameConfig",
                "SmallWorld/Public/GameData",
                "SmallWorld/Public/GameData/BuildingData",
                "SmallWorld/Public/GameData/GameConfigData",
                "SmallWorld/Public/GameData/SoldierData",
                "SmallWorld/Public/GameData/UserData",
                "SmallWorld/Public/GamePath",
                "SmallWorld/Public/Goals",
                "SmallWorld/Public/Goals/LevelOne",
                "SmallWorld/Public/Goals/LevelThree",
                "SmallWorld/Public/Goals/LevelTwo",
                "SmallWorld/Public/GamePath",
                "SmallWorld/Public/Goals",
                "SmallWorld/Public/Group",
                "SmallWorld/Public/Tools",
                "SmallWorld/Public/UI",
                "SmallWorld/Public/UI/SlateStyles",
                "SmallWorld/Public/UI/Widgets",
                "SmallWorld/Public/UI/Widgets/MenuBuilder",
                "SmallWorld/Public/UserInterface",
                "SmallWorld/Public/Weapons",
           }
           );
       
        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "AIModule",
            "GameplayTasks",
            "NavigationSystem",
            "Json",
            "Slate",
            "SlateCore",
            "UnrealEd",
            "Landscape",
            "Foliage",
            "EditLandscape",
            "XmlParser",
            "MiniMap",
            "GCore",
            "ProceduralMesh",
            "SlateUI",
            "UnrealEngineWrap",
            "GameFrame",
            "ProgressTimer"
        });

        //PrivateDependencyModuleNames.AddRange(new string[] {  });

        // Uncomment if you are using Slate UI
        PrivateDependencyModuleNames.AddRange(new string[] {
            "Slate",
            "SlateCore",
            "RenderCore",
            "RHI",
        });
       
        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
