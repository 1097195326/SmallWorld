#include "RDRunCmd.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include <Windows.h>
#include "Windows/HideWindowsPlatformTypes.h"


void CRunCmd::RunCmd(const FString& InCmd)
{
	const int cstLen = WideCharToMultiByte(CP_ACP, 0, *InCmd, -1, NULL, 0, NULL, NULL);
	char *pChCmd = new char[cstLen];
	WideCharToMultiByte(CP_ACP, 0, *InCmd, -1, pChCmd, cstLen, NULL, NULL);
	const uint32& cstRst = system(pChCmd);
	delete pChCmd;
	pChCmd = nullptr;
	if (cstRst != 0)
	{
		//const FText OptTitle = FText::FromString(FString::Printf(L"���� %s ʧ��", *FPaths::GetBaseFilename(PakFilename)));
		//FMessageDialog::Debugf(FText::FromString(L"Windows�����쳣"), &OptTitle);
	}
}

void CRunCmd::RunExe(const FString& InExeFile, const FString& InExeParam)
{
	void* PipeRead = nullptr;
	void* PipeWrite = nullptr;
	int32 ReturnCode = -1;

	verify(FPlatformProcess::CreatePipe(PipeRead, PipeWrite));
	bool bLaunchDetached = false;
	bool bLaunchHidden = true;
	bool bLaunchReallyHidden = true;
	uint32* OutProcessID = nullptr;
	int32 PriorityModifier = -1;
	const TCHAR* OptionalWorkingDirectory = nullptr;
	FProcHandle ProcessHandle = FPlatformProcess::CreateProc(
		*InExeFile, *InExeParam,
		bLaunchDetached, bLaunchHidden, bLaunchReallyHidden,
		OutProcessID, PriorityModifier,
		OptionalWorkingDirectory,
		PipeWrite
	);


	if (ProcessHandle.IsValid())
	{
		FPlatformProcess::WaitForProc(ProcessHandle);
		FPlatformProcess::GetProcReturnCode(ProcessHandle, &ReturnCode);
		if (ReturnCode == 0)
		{
			TArray<FString> OutResults;
			const FString StdOut = FPlatformProcess::ReadPipe(PipeRead);
			StdOut.ParseIntoArray(OutResults, TEXT("\n"), true);
			//UE_LOG(LogTemp, Log, TEXT("NOPPakTool success:\n%s"), *StdOut);
		}
		else
		{
			TArray<FString> OutErrorMessages;
			const FString StdOut = FPlatformProcess::ReadPipe(PipeRead);
			StdOut.ParseIntoArray(OutErrorMessages, TEXT("\n"), true);
			//UE_LOG(LogTemp, Warning, TEXT("NOPPakTool Falied:\nReturnCode=%d\n%s"), ReturnCode, *StdOut);
		}

		FPlatformProcess::ClosePipe(PipeRead, PipeWrite);
		FPlatformProcess::CloseProc(ProcessHandle);
	}
	else
	{
		//UE_LOG(LogTemp, Error, TEXT(" Failed to launch unrealPak.exe: %s"), *UnrealPakExeFilepath);
	}
}
