// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Network1 : ModuleRules
{
	public Network1(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay",
															"Http", "Json", "JsonUtilities",
															"UMG" });

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
	}
}
