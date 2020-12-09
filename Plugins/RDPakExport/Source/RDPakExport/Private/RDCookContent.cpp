#include "RDCookContent.h"
#include "RDRunCmd.h"

#define CookProject TEXT("{\"FileVersion\":3,\"EngineAssociation\":\"4.22\"}")

CCookContent::CCookContent(const TArray<FString>& InFilesCook)
{
	ClearFilesFromDir(m_cstCookPrjDir);

	const FString& cstCookPrjFile = m_cstCookPrjDir / m_cstCookedProjectName;
	FFileHelper::SaveStringToFile(CookProject, *cstCookPrjFile);

	const FString& cstCPContentDir = m_cstCookPrjDir / L"Content/";
	CopyFilesToDir(InFilesCook, cstCPContentDir);
}

CCookContent::~CCookContent()
{
	ClearFilesFromDir(m_cstCookPrjDir);
}

void CCookContent::Cook(const TSet<ETargetPlatform>& InPlatformSet, TArray<SCookedInfo>& OutCookedInfList)
{
	const FString& strUE4EditorExe = FPaths::ConvertRelativePathToFull(FPaths::EngineDir() / TEXT("Binaries/Win64") / TEXT("UE4Editor-Cmd.exe"));

	TArray<FString> arrPlatform;
	const FString& cstCookPrj = m_cstCookPrjDir / m_cstCookedProjectName;
	FString strPlatformList;
	const UEnum* pEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("ETargetPlatform"), true);
	for (auto ePlatformIt = InPlatformSet.CreateConstIterator(); ePlatformIt; ++ePlatformIt)
	{
		auto idx = pEnum->GetIndexByValue((uint8)*ePlatformIt);
		FString strPlatform = pEnum->GetDisplayNameTextByIndex(idx).ToString();
		arrPlatform.Emplace(strPlatform);
		if (*ePlatformIt == ETargetPlatform::E_Editor)
		{
			continue;
		}

		const FString& strCookedDir = m_cstCPSavedDir / L"Cooked" / strPlatform / FPaths::GetBaseFilename(m_cstCookedProjectName) / L"Content";
		ClearFilesFromDir(strCookedDir);
		strPlatformList = strPlatformList + L"+" + strPlatform;
	}
	if (!strPlatformList.IsEmpty())
	{
		const FString& strUE4EditorParams = FString::Printf(TEXT("\"%s\" -Run=cook -targetplatform=\"%s\" -iterate -Compressed"), *cstCookPrj, *strPlatformList);
		const FString& strCmd = FString::Printf(TEXT("\"\"%s\" %s\""), *strUE4EditorExe, *strUE4EditorParams);

		CRunCmd runCmd;
		runCmd.RunCmd(strCmd);
		//runCmd.RunExe(strUE4EditorExe, strUE4EditorParams);
	}
	GetCookedInfo(arrPlatform, OutCookedInfList);
}

void CCookContent::GetCookedInfo(const TArray<FString>& InPlatformList, TArray<SCookedInfo>& OutCookedInfList)
{
	FString editorEnumStr;
	if (const UEnum* pEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("ETargetPlatform"), true))
	{
		editorEnumStr = pEnum->GetDisplayNameTextByValue((int64)ETargetPlatform::E_Editor).ToString();
	}
	for (auto& strPlatform : InPlatformList)
	{
		SCookedInfo sCookedInf;
		sCookedInf.TargetPlatform = strPlatform;
		if (strPlatform.Equals(editorEnumStr))
		{
			sCookedInf.CookedContentDir = m_cstCookPrjDir / L"Content/";
		}
		else
		{
			sCookedInf.CookedContentDir = m_cstCPSavedDir / L"Cooked" / strPlatform / FPaths::GetBaseFilename(m_cstCookedProjectName) / L"Content/";
		}
		GetFileListInDir(sCookedInf.CookedContentDir, sCookedInf.FileList);
		OutCookedInfList.Emplace(sCookedInf);
	}
}

void CCookContent::CopyFilesToDir(const TArray<FString>& InFiles, const FString& InDestDir)
{
	for (auto& strFilename : InFiles)
	{
		if (!FPaths::FileExists(strFilename))
		{
			continue;
		}
		const FString& strDesFilename = strFilename.Replace(*FPaths::ProjectContentDir(), *InDestDir);
		const FString& strDesDir = FPaths::GetPath(strDesFilename);
		if (!FPaths::DirectoryExists(strDesDir))
		{
			IFileManager::Get().MakeDirectory(*strDesDir, true);
		}
		IFileManager::Get().Copy(*strDesFilename, *strFilename);
	}
}

void CCookContent::ClearFilesFromDir(const FString & InDir)
{
	IFileManager::Get().DeleteDirectory(*InDir, false, true);
}

void CCookContent::GetFileListInDir(const FString& InDir, TArray<FString>& OutFileList)
{
	FString strDirSerch = InDir / "*.*";
	TArray<FString> arrFileOrDir;
	IFileManager::Get().FindFiles(arrFileOrDir, *strDirSerch, true, true);
	for (auto& strFileOrDir : arrFileOrDir)
	{
		FString strFullPath = InDir / strFileOrDir;
		if (FPaths::DirectoryExists(strFullPath))
		{
			GetFileListInDir(strFullPath, OutFileList);
		}
		else
		{
			OutFileList.Emplace(strFullPath);
		}
	}
}
