using UnrealBuildTool;

public class HECSModule : ModuleRules
{
    public HECSModule(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore"
            }
        );
        
        PublicIncludePaths.AddRange(new string[] {"HECSModule/Public"});
        PrivateIncludePaths.AddRange(new string[] {"HECSModule/Private"});
    }
}