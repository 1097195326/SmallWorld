#pragma once


UENUM(BlueprintType)
enum class ETargetPlatform : uint8
{
	E_Editor			UMETA(DisplayName = "Editor"),
	E_WindowsNoEditor	UMETA(DisplayName = "WindowsNoEditor"),
	E_WindowsServer		UMETA(DisplayName = "WindowsServer"),
	E_LinuxServer		UMETA(DisplayName = "LinuxServer"),
	E_PS4				UMETA(DisplayName = "PS4"),
	E_XboxOne			UMETA(DisplayName = "XboxOne"),
	E_IOS				UMETA(DisplayName = "IOS"),
	E_Android			UMETA(DisplayName = "Android")
};

class CCookContent
{
public:
	struct SCookedInfo
	{
		FString TargetPlatform;
		FString CookedContentDir;
		TArray<FString> FileList;
		SCookedInfo()
			: TargetPlatform()
			, CookedContentDir()
		{
			FileList.Empty();
		}
	};

	CCookContent(const TArray<FString>& InFilesCook);
	~CCookContent();
	void Cook(const TSet<ETargetPlatform>& InPlatformSet, TArray<SCookedInfo>& OutCookedInfList);
	void GetCookedInfo(const TArray<FString>& InPlatformList, TArray<SCookedInfo>& OutCookedInfList);

private:
	void CopyFilesToDir(const TArray<FString>& InFiles, const FString& InDestDir);
	void ClearFilesFromDir(const FString& InDir);

	void GetFileListInDir(const FString& InDir, TArray<FString>& OutFileList);

private:
	const FString& m_cstCookPrjDir = FPaths::ProjectPluginsDir() / L"RDPakExport" / L"CookProject/";
	const FString& m_cstCPSavedDir = m_cstCookPrjDir / L"Saved/";
	const FString& m_cstCookedProjectName = L"Cook.uproject";
};