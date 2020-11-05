#pragma once


class CCreatePakFile
{
public:
	CCreatePakFile(const FString& InPakFilename);
	void CreatePak(const TArray<FString>& InFilesPackage, const FString& InMainPath, const FString& InDescriptionString);

private:
	const TArray<FString> m_arrFilePackage;
	const FString& m_strPakFilename;
};
