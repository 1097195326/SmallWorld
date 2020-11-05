#include "RDPakExportSettings.h"

URDPakExportSettings::URDPakExportSettings()
	: bEditor(false)
	, bWindows(true)
	, bAndroid(false)
	, bIOS(false)
	, bPS4(false)
	, bXboxOne(false)
	, bCompress(true)
	, SavedDir(FPaths::ProjectDir() / "Paks")
	, m_cfgFile()
	//, m_cfgFile(FString::Printf(TEXT("%s/PakExport/Config/Setting.cfg"), *FPaths::ProjectPluginsDir()))
{
	m_cfgFile.IsEmpty() ? LoadConfig() : LoadConfig(nullptr, *m_cfgFile);
	UpdatePlatforms();
}

URDPakExportSettings* URDPakExportSettings::Get()
{
	URDPakExportSettings* DefaultSettings = GetMutableDefault<URDPakExportSettings>();
	return DefaultSettings;
}

void URDPakExportSettings::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	UpdatePlatforms();
	m_cfgFile.IsEmpty() ? SaveConfig() : SaveConfig(CPF_Config, *m_cfgFile);
}

void URDPakExportSettings::SetSavedDir(const FString& InSavedDir)
{
	SavedDir = InSavedDir;
	FPropertyChangedEvent nullEvent(nullptr);
	PostEditChangeProperty(nullEvent);
}

void URDPakExportSettings::SetPackagesToExport(const TArray<FAssetData>& InPackagesToExport)
{
	m_packagesToExport = InPackagesToExport;
	ObjectsToExport.Empty();
	for (const FAssetData& assetData : m_packagesToExport)
	{
		ObjectsToExport.Add(assetData.FastGetAsset(true));
	}
}

const TArray<FAssetData>& URDPakExportSettings::GetPackagesToExport() const
{
	return m_packagesToExport;
}

const TSet<ETargetPlatform>& URDPakExportSettings::GetPlatforms() const
{
	return m_platforms;
}

void URDPakExportSettings::UpdatePlatforms()
{
	if (bEditor) m_platforms.Add(ETargetPlatform::E_Editor);
	else m_platforms.Remove(ETargetPlatform::E_Editor);

	if (bWindows) m_platforms.Add(ETargetPlatform::E_WindowsNoEditor);
	else m_platforms.Remove(ETargetPlatform::E_WindowsNoEditor);

	if (bAndroid) m_platforms.Add(ETargetPlatform::E_Android);
	else m_platforms.Remove(ETargetPlatform::E_Android);

	if (bIOS) m_platforms.Add(ETargetPlatform::E_IOS);
	else m_platforms.Remove(ETargetPlatform::E_IOS);

	if (bPS4) m_platforms.Add(ETargetPlatform::E_PS4);
	else m_platforms.Remove(ETargetPlatform::E_PS4);

	if (bXboxOne) m_platforms.Add(ETargetPlatform::E_XboxOne);
	else m_platforms.Remove(ETargetPlatform::E_XboxOne);
}
