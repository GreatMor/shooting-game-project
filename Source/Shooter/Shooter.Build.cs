// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Shooter : ModuleRules
{
	public Shooter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
		{ "Core",
		  "CoreUObject",
		  "Engine",
		  "InputCore", 
		  "Niagara",
		  "PhysicsCore",
		  "GameplayTasks",
		  "NavigationSystem",
		  "AIModule"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.AddRange(new string[]
		{"Shooter/Public/Player",
		 "Shooter/Public/Dev",
		 "Shooter/Public/Weapon",
		 "Shooter/Public/UI",
		 "Shooter/Public/FXComponents",
		 "Shooter/Public/AI",
		 "Shooter/Public/AI/Tasks",
		 "Shooter/Public/AI/Components",
		 "Shooter/Public/Player/Components",
		 "Shooter/Public/AI/Services",
		 "Shooter/Public/AI/EQS",
		 "Shooter/Public/AI/Decorator",
         "Shooter/Public/Menu",
         "Shooter/Public/Menu/UI"
        });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
