// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UE_Portal : ModuleRules
{
	public UE_Portal(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
