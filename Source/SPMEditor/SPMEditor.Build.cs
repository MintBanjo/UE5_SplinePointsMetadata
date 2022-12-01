// Copyright Paul Brocklehurst 2022

using UnrealBuildTool;

public class SPMEditor : ModuleRules
{
    public SPMEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "SPM",
            "DetailCustomizations",
            "Slate",
            "SlateCore",
            "UnrealEd",
            "PropertyEditor",
            "EditorStyle"
        });
    }
}
