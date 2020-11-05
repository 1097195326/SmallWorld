#include "RDGetExportData.h"
#include "LevelEditor.h"
#include "Interfaces/IMainFrameModule.h"
#include "ContentBrowserModule.h"
#include "AssetRegistryModule.h"
#include "DesktopPlatformModule.h"
#include "FileHelpers.h"
#include "IContentBrowserSingleton.h"
#include "JsonObjectConverter.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include <Windows.h>
#include "Windows/HideWindowsPlatformTypes.h"


CGetExportData::CGetExportData(const FAssetData& InAssetSelect)
	: m_assetExport(InAssetSelect)
	, m_pakDescription()
{
	FContentBrowserModule& contentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");

	m_pakDescription.MainAsset.ObjectPath = m_assetExport.ObjectPath;
	m_pakDescription.MainAsset.PackageName = m_assetExport.PackageName;
	m_pakDescription.MainAsset.PackagePath = m_assetExport.PackagePath;
	m_pakDescription.MainAsset.AssetName = m_assetExport.AssetName;
	m_pakDescription.MainAsset.AssetClass = m_assetExport.AssetClass;

	//m_pakDescription.MainAsset.PackageName = InAssetSelect.PackageName.ToString();
	//m_pakDescription.MainAsset.AssetName = InAssetSelect.AssetName.ToString();
	//if (InAssetSelect.AssetClass == UBlueprint::StaticClass()->GetFName() || InAssetSelect.GetClass()->IsChildOf(UBlueprint::StaticClass()))
	//{
	//	m_pakDescription.MainAsset.AssetType = E_PE_AssetType::BlueprintClass;
	//}
	//else if (InAssetSelect.AssetClass == UMaterial::StaticClass()->GetFName() || InAssetSelect.GetClass()->IsChildOf(UMaterial::StaticClass()))
	//{
	//	m_pakDescription.MainAsset.AssetType = E_PE_AssetType::Material;
	//}
	//else if (InAssetSelect.AssetClass == UMaterialInstance::StaticClass()->GetFName() || InAssetSelect.GetClass()->IsChildOf(UMaterialInstance::StaticClass()))
	//{
	//	m_pakDescription.MainAsset.AssetType = E_PE_AssetType::MaterialInst;
	//}
	//else if (InAssetSelect.AssetClass == UWorld::StaticClass()->GetFName() || InAssetSelect.GetClass()->IsChildOf(UWorld::StaticClass()))
	//{
	//	m_pakDescription.MainAsset.AssetType = E_PE_AssetType::Level;
	//}
	//else
	//{
	//	m_pakDescription.MainAsset.AssetType = E_PE_AssetType::Others;
	//}
}


void CGetExportData::GetDefaultExportFilename(const FString& InDir, FString& OutFilename)
{
	OutFilename = FString::Printf(L"%s/%s.pak", *InDir, *m_assetExport.PackageName.ToString());
}

void CGetExportData::GetAllFilesExport(TArray<FString>& OutFileList)
{
	if (!FEditorFileUtils::SaveDirtyPackages(true, true, true))
	{
		return;
	}

	const FString& mainPackage = m_assetExport.PackageName.ToString();
	TSet<FName> arrAllPackageExport;
	arrAllPackageExport.Add(*mainPackage);
	RecursiveGetDependencies(*mainPackage, arrAllPackageExport);
	m_pakDescription.PackagesDependency = arrAllPackageExport.Array();

	//需要打包pak的所有文件路径信息
	FString PakInfoContent;
	for (auto packageIt = arrAllPackageExport.CreateConstIterator(); packageIt; ++packageIt)
	{
		const FString& strPackageName = (*packageIt).ToString();
		FString strPackageFilename;
		if (!FPackageName::DoesPackageExist(strPackageName, nullptr, &strPackageFilename))
		{
			const FString WarnMessage = FString::Printf(TEXT("\"%s\" does not exist on disk."), *strPackageName);
			//UE_LOG(PAKLog, Warning, TEXT("%s"), *WarnMessage);
			continue;
		}
		OutFileList.Emplace(strPackageFilename);
	}
}

void CGetExportData::GetAssetDescription(FString& OutJsonString)
{
	FJsonObjectConverter::UStructToJsonObjectString(m_pakDescription, OutJsonString);
}

//获取所有依赖的资源
void CGetExportData::RecursiveGetDependencies(const FName& PackageName, TSet<FName>& AllDependencies) const
{
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::Get().LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	TArray<FName> Dependencies;
	AssetRegistryModule.Get().GetDependencies(PackageName, Dependencies);

	for (auto DependsIt = Dependencies.CreateConstIterator(); DependsIt; ++DependsIt)
	{
		if (!AllDependencies.Contains(*DependsIt))
		{
			const bool bIsEnginePackage = (*DependsIt).ToString().StartsWith(TEXT("/Engine"));
			const bool bIsScriptPackage = (*DependsIt).ToString().StartsWith(TEXT("/Script"));
			if (!bIsEnginePackage && !bIsScriptPackage)
			{
				AllDependencies.Add(*DependsIt);
				RecursiveGetDependencies(*DependsIt, AllDependencies);
			}
		}
	}
}

bool CAssetsSelect::SelectAssets(TArray<FAssetData>& OutAssetsSelect)
{
	OutAssetsSelect.Empty();
	FContentBrowserModule& contentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	contentBrowserModule.Get().GetSelectedAssets(OutAssetsSelect);
	if (OutAssetsSelect.Num() < 1)
	{
		const FText OptTitle = FText::FromString(L"警告");
		FMessageDialog::Debugf(FText::FromString(L"未选择任何资源文件"), &OptTitle);
		return false;
	}
	return true;
}

bool CAssetsSelect::SelectSavePath(FString& OutFilePath)
{
	IDesktopPlatform* pDesktopPlatform = FDesktopPlatformModule::Get();
	if (!pDesktopPlatform)
	{
		//const FString ErrorMessage = TEXT("DesktopPlatform Get Error.");
		//UE_LOG(PAKLog, Error, TEXT("%s"), *ErrorMessage);
		return false;
	}
	void* pParentWindowHandle = nullptr;
	IMainFrameModule& mainFrameModule = FModuleManager::LoadModuleChecked<IMainFrameModule>(TEXT("MainFrame"));
	const TSharedPtr<SWindow>& spParentWindow = mainFrameModule.GetParentWindow();
	if (spParentWindow.IsValid() && spParentWindow->GetNativeWindow().IsValid())
	{
		pParentWindowHandle = spParentWindow->GetNativeWindow()->GetOSWindowHandle();
	}
	const FString& strDefaultPath = FPaths::ProfilingDir() + TEXT("PAKFilesCache");
	bool bRst = pDesktopPlatform->OpenDirectoryDialog(
		pParentWindowHandle,
		TEXT("Choose file location"),
		strDefaultPath,
		OutFilePath
	);
	if (!bRst)
	{
		const FString ErrorMessage = TEXT("No file path select.");
		//UE_LOG(PAKLog, Error, TEXT("%s"), *ErrorMessage);
		return false;
	}
	return true;
}
