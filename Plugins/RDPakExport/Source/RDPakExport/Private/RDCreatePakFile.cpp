#include "RDCreatePakFile.h"
#include "RDRunCmd.h"


CCreatePakFile::CCreatePakFile(const FString & InPakFilename)
	: m_strPakFilename(InPakFilename)
{
}

void CCreatePakFile::CreatePak(const TArray<FString>& InFilesPackage, const FString& InMainPath, const FString& InDescriptionString)
{
	if (InFilesPackage.Num() < 1)
	{
		return;
	}
	if (InDescriptionString.IsEmpty())
	{
		return;
	}
	FString strDescriptionFilename = InMainPath / FGuid::NewGuid().ToString() + L".json";
	if (!FFileHelper::SaveStringToFile(InDescriptionString, *strDescriptionFilename))
	{
		return;
	}

	TArray<FString> arrFilePackage;
	arrFilePackage.Append(InFilesPackage);
	arrFilePackage.Emplace(strDescriptionFilename);

	//需要打包pak的所有文件路径信息
	FString strCreateFileContent;
	for (const FString& strSrcFilename : arrFilePackage)
	{
		const FString& cstBZHeadPath = TEXT("RDDLC/Content/");
		const FString& strDesFilename = strSrcFilename.Replace(*InMainPath, *cstBZHeadPath);
		if (!FPaths::FileExists(strSrcFilename))
		{
			const FString WarnMessage = FString::Printf(TEXT("\"%s\" does not exist on disk."), *strSrcFilename);
			//UE_LOG(PAKLog, Warning, TEXT("%s"), *WarnMessage);
			continue;
		}

		strCreateFileContent += FString::Printf(TEXT("\"%s\" \"%s\""), *strSrcFilename, *strDesFilename);
		strCreateFileContent += LINE_TERMINATOR;
	}
	if (strCreateFileContent.IsEmpty())
	{
		//const FText OptTitle = FText::FromString(FString::Printf(L"导出 %s 失败", *FPaths::GetBaseFilename(m_strPakFilename)));
		//FMessageDialog::Debugf(FText::FromString(L"未找到所需资源文件,详情看日志"), &OptTitle);
		return;
	}

	const FString& strCreateFilename = *(FPaths::EngineVersionAgnosticUserDir() + TEXT("PackageData.udd"));
	const bool& bFileSaved = FFileHelper::SaveStringToFile(strCreateFileContent, *strCreateFilename, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
	if (!bFileSaved)
	{
		const FString ErrorMessage = TEXT("SaveStringToFileError.");
		//UE_LOG(PAKLog, Error, TEXT("%s"), *ErrorMessage);

		//const FText OptTitle = FText::FromString(FString::Printf(L"导出 %s 失败", *FPaths::GetBaseFilename(m_strPakFilename)));
		//FMessageDialog::Debugf(FText::FromString(L"本地化失败"), &OptTitle);
		return;
	}
	const FString& strUnrealPakParams = FString::Printf(TEXT("\"%s\" -Create=\"%s\" -compress"), *m_strPakFilename, *strCreateFilename);
	const FString& strUnrealPakExe = FPaths::ConvertRelativePathToFull(FPaths::EngineDir() / TEXT("Binaries/Win64") / TEXT("UnrealPak.exe"));

	CRunCmd runCmd;
	//const FString& strCmd = FString::Printf(TEXT("\"\"%s\" %s\""), *strUnrealPakExe, *strUnrealPakParams);
	//runCmd.Run(strCmd);
	runCmd.RunExe(strUnrealPakExe, strUnrealPakParams);
	IFileManager::Get().Delete(*strDescriptionFilename);
}
