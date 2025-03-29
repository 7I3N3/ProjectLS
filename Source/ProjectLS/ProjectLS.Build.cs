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
			"EnhancedInput"
		});
		PrivateDependencyModuleNames.AddRange(new string[]
		{

		});

		PublicIncludePaths.AddRange(new string[]
		{
			"ProjectLS/Public",
            "ProjectLS/Public/Interfaces"
        });
		PrivateIncludePaths.AddRange(new string[]
		{
            "ProjectLS/Private",
            "ProjectLS/Private/Interfaces"
        });
    }
}
