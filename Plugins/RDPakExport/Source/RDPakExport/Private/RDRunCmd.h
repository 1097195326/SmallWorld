#pragma once
#include "Engine.h"

class CRunCmd
{
public:
	void RunCmd(const FString& InCmd);
	void RunExe(const FString& InExeFile, const FString& InExeParam);
};