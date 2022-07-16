// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class QuestVer2 : ModuleRules
{
	public QuestVer2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
