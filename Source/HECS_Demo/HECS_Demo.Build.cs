// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HECS_Demo : ModuleRules
{
	public HECS_Demo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
