// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class RealSenseSamples : ModuleRules
{
    private string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty/")); }
    }

	public RealSenseSamples(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
        LoadOpenCV(Target);

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}

    public bool LoadOpenCV(ReadOnlyTargetRules Target)
    {
        // Start OpenCV linking here
        bool islibrarySupported = false;

        // Create OpenCV Path
        string OpenCVPath = Path.Combine(ThirdPartyPath, "OpenCV");

        //Get Library Path
        string LibPath = "";
        // bool isdebug = Target.Configuration == UnrealTargetConfiguration.Debug && BuildConfiguration.bDebugBuildActuallyUseDebugCRT;
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            LibPath = Path.Combine(OpenCVPath, "Libraries", "Win64");
            islibrarySupported = true;
        }
        else
        {
            string Err = string.Format("{0} dedicated server is made to depend on {1}. We want to aboid this, please correct module dependencies.", Target.Platform.ToString(), this.ToString());
            System.Console.WriteLine(Err);
        }

        if (islibrarySupported)
        {
            // Add Include Path
            PublicIncludePaths.AddRange(new string[] { Path.Combine(OpenCVPath, "Includes") });

            // Add Library Path
            PublicLibraryPaths.Add(LibPath);

            // Add Static Libraries
            PublicAdditionalLibraries.Add("opencv_world345.lib");

            // Add Dynamic Libraries
            PublicDelayLoadDLLs.Add("opencv_world345.dll");
            PublicDelayLoadDLLs.Add("opencv_ffmpeg345_64.dll");

        }

        PublicDefinitions.Add(string.Format("WITH_OPENCV_BINDING={0}", islibrarySupported ? 1 : 0));

        return islibrarySupported;
    }
}
