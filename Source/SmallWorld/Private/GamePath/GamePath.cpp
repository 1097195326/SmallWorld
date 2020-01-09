#include "GamePath.h"


FString GamePath::SaveAbsolutePath()
{
#if PLATFORM_WINDOWS
	static FString persistentDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectSavedDir(), TEXT(""));
#elif PLATFORM_ANDROID
	static FString persistentDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectPersistentDownloadDir(), TEXT(""));
#else
	IPlatformFile &  pf = FPlatformFileManager::Get().GetPlatformFile();
	FString AppendPath = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT(""));
	static FString persistentDir = pf.ConvertToAbsolutePathForExternalAppForWrite(*AppendPath);
#endif
	//UE_LOG(LogTemp,Log,TEXT("zhx : SaveAbsolutePath : %s"),*persistentDir);
	return persistentDir;
}
FString GamePath::IOSSavePath()
{
	FString downDir = SaveAbsolutePath();
	FString iosDir = ExtractIOSDir(*downDir);
	return iosDir;
}
FString GamePath::ProjectPath(const TCHAR * appPath)
{
	IPlatformFile &  pf = FPlatformFileManager::Get().GetPlatformFile();
	FString AppendPath = FPaths::Combine(FPaths::ProjectDir(), appPath);
#if PLATFORM_WINDOWS
	return AppendPath;
#elif PLATFORM_ANDROID
	//Rp = FPaths::ConvertRelativePathToFull(FPaths::ProjectPersistentDownloadDir(), AppendPath);
#else
	FString iosAbsPath = pf.ConvertToAbsolutePathForExternalAppForWrite(*AppendPath);
	return ExtractIOSDir(*iosAbsPath);
#endif
}
FString GamePath::ExtractIOSDir(const TCHAR * DirPath)
{
	string cDirPath = TCHAR_TO_UTF8(DirPath);
	string cSource = ExtractIOSDir(cDirPath);
	return FString(UTF8_TO_TCHAR(cSource.c_str()));
}
string GamePath::ExtractIOSDir(const string &DirPath)
{
#if PLATFORM_IOS
	FString rootDir = IFileManager::Get().ConvertToAbsolutePathForExternalAppForWrite(TEXT(""));
	std::string sRootDir(TCHAR_TO_UTF8(*rootDir));
	int len = DirPath.length();
	string folder = DirPath.substr(0, len);
	if (string::npos != DirPath.find(sRootDir))
	{
		int flen = sRootDir.length();
		folder = DirPath.substr(flen, len);
	}
	return folder;
#else
	return DirPath;
#endif
	}