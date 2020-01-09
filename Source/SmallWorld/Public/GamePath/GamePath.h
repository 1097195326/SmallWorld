#pragma once

#include "SingleTemplate.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFilemanager.h"
#include <string>


using namespace std;


class GamePath : public SingleTemplate<GamePath>
{
public:



private:
	FString ProjectHotloadDownloadDir();
	string	ExtractIOSDir(const string &DirPath);
	FString ExtractIOSDir(const TCHAR * DirPath);
	FString GetIOSDir();
	FString GetAppPath(const TCHAR * appPath = TEXT(""));

};