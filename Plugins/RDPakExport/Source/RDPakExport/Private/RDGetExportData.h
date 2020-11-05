#pragma once
#include "Engine.h"
#include "RDGetExportData.generated.h"

UENUM()
enum class E_PE_DescriptionVersion : uint8
{
	V_1,
	V_2,
	V_3,
	V_4,
	V_5,
	V_Last
};

//UENUM()
//enum class E_PE_AssetType : uint8
//{
//	BlueprintClass,
//	Material,
//	MaterialInst,
//	Level,
//	Others,
//	None,
//};
//
//USTRUCT()
//struct F_PE_AssetDescription
//{
//	GENERATED_BODY()
//
//
//	UPROPERTY()
//	FString AssetName;
//
//	UPROPERTY()
//		E_PE_AssetType AssetType;
//
//	UPROPERTY()
//		FString PackageName;
//
//	F_PE_AssetDescription()
//		: AssetName()
//		, AssetType(E_PE_AssetType::None)
//		, PackageName()
//	{
//
//	}
//};
USTRUCT()
struct F_PE_PakAssetData
{
	GENERATED_BODY()

	UPROPERTY()
		FName ObjectPath;

	UPROPERTY()
		FName PackageName;

	UPROPERTY()
		FName PackagePath;

	UPROPERTY()
		FName AssetName;

	UPROPERTY()
		FName AssetClass;

	F_PE_PakAssetData()
		: ObjectPath()
		, PackageName()
		, PackagePath()
		, AssetName()
		, AssetClass()
	{

	}
};

USTRUCT()
struct F_PE_PakDescription
{
	GENERATED_BODY()

	UPROPERTY()
	E_PE_DescriptionVersion Version;

	UPROPERTY()
		F_PE_PakAssetData MainAsset;

	UPROPERTY()
	TArray<FName> PackagesDependency;

	F_PE_PakDescription()
		: Version(E_PE_DescriptionVersion::V_1)
		, MainAsset()
	{
		PackagesDependency.Empty();
	}
};

class CAssetsSelect
{
public:
	static bool SelectAssets(TArray<FAssetData>& OutAssetsSelect);
	static bool SelectSavePath(FString& OutFilePath);
};

class CGetExportData
{
public:
	void GetAllFilesExport(TArray<FString>& OutFileList);
	void GetAssetDescription(FString& OutJsonString);

	CGetExportData(const FAssetData& InAssetSelect);
	void GetDefaultExportFilename(const FString& InDir, FString& OutFilename);

private:
	void RecursiveGetDependencies(const FName& PackageName, TSet<FName>& AllDependencies) const;

private:
	const FAssetData& m_assetExport;
	F_PE_PakDescription m_pakDescription;
};
