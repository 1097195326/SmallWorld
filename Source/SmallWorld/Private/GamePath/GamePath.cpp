#include "GamePath.h"






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
FString GamePath::ProjectHotloadDownloadDir()
{
#if PLATFORM_WINDOWS
	static FString persistentDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectSavedDir(), TEXT("dlc/paks/"));
#elif PLATFORM_ANDROID
	static FString persistentDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectPersistentDownloadDir(), TEXT("dlc/paks/"));
#else
	IPlatformFile &  pf = FPlatformFileManager::Get().GetPlatformFile();
	FString AppendPath = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("dlc/paks/"));
	static FString persistentDir = pf.ConvertToAbsolutePathForExternalAppForWrite(*AppendPath);
#endif
	//UE_LOG(LogTemp,Log,TEXT("zhx : ProjectHotloadDownloadDir : %s"),*persistentDir);

	return persistentDir;
}
FString GamePath::GetIOSDir()
{
	FString downDir = ProjectHotloadDownloadDir();
	//UE_LOG(LogTemp,Log,TEXT("zhx : downDir : %s"),*downDir);
	FString iosDir = ExtractIOSDir(*downDir);
	//UE_LOG(LogTemp,Log,TEXT("zhx : iosDir : %s"),*iosDir);

	return iosDir;
}
FString GamePath::GetAppPath(const TCHAR * appPath)
{
	IPlatformFile &  pf = FPlatformFileManager::Get().GetPlatformFile();
	FString AppendPath = FPaths::Combine(FPaths::ProjectDir(), appPath);

#if PLATFORM_WINDOWS
	return AppendPath;
#elif PLATFORM_ANDROID
	Rp = FPaths::ConvertRelativePathToFull(FPaths::ProjectPersistentDownloadDir(), appPath);
#else
	FString iosAbsPath = pf.ConvertToAbsolutePathForExternalAppForWrite(*AppendPath);

	return ExtractIOSDir(*iosAbsPath);
#endif

}
