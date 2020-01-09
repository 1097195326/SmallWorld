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

	FString SaveAbsolutePath();
	FString IOSSavePath();
	FString ProjectPath(const TCHAR * appPath = TEXT(""));


private:
	string	ExtractIOSDir(const string &DirPath);
	FString ExtractIOSDir(const TCHAR * DirPath);

};