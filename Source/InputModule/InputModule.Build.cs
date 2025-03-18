// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class InputModule : ModuleRules
{
	public InputModule(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "ProjectLS" });

		PrivateDependencyModuleNames.AddRange(new string[] { "EnhancedInput", "ProjectLS" });

		PublicIncludePaths.AddRange(new string[] { "InputModule/Public" });
		PrivateIncludePaths.AddRange(new string[] { "InputModule/Private" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
