#pragma once

#include "SingleTemplate.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFilemanager.h"
#include <string>


using namespace std;


class GamePath
{
public:

	static FString SaveAbsolutePath();
	static FString IOSSavePath();
	static FString GameConfigPath();

	static FString ProjectPath(const TCHAR * appPath = TEXT(""));


private:
	static string	ExtractIOSDir(const string &DirPath);
	static FString ExtractIOSDir(const TCHAR * DirPath);

};