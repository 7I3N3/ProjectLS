// Copyright Epic Games, Inc. All Rights Reserved.

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
			"UMG"
		});
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Slate",
			"SlateCore",
            "GameplayAbilities", 
			"GameplayTags", 
			"GameplayTasks"
        });

		PublicIncludePaths.AddRange(new string[]
		{
			"ProjectLS/Public",
            "ProjectLS/Public/Interfaces",
            "ProjectLS/Public/Items",
            "ProjectLS/Public/Widgets"
        });
		PrivateIncludePaths.AddRange(new string[]
		{
            "ProjectLS/Private",
            "ProjectLS/Private/Interfaces",
            "ProjectLS/Private/Items",
            "ProjectLS/Private/Widgets"
        });
    }
}
