// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class ProjectLS : ModuleRules
{
	public ProjectLS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
        { 
            "Core", 
            "CoreUObject", 
            "Engine", 
            "InputCore", 
            "EnhancedInput", 
            "InputModule" 
        });

		PrivateDependencyModuleNames.AddRange(new string[] 
        { 
            "InputModule",
            "GameplayAbilities",
            "GameplayTags",
            "GameplayTasks"
        });

		PublicIncludePaths.AddRange(new string[]
		{
			"ProjectLS/Public/Item"
        });

        PrivateIncludePaths.AddRange(new string[]
        {
            "ProjectLS/Private/Item"
        });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
