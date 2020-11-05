#pragma once
#include "Engine.h"
#include "RDCookContent.h"
#include "RDPakExportSettings.generated.h"


UCLASS(config = EditorPESettings)
class URDPakExportSettings : public UObject
{
	GENERATED_BODY()
public:
	URDPakExportSettings();
	static URDPakExportSettings* Get();
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

	void SetSavedDir(const FString& InSavedDir);
	void SetPackagesToExport(const TArray<FAssetData>& InPackagesToExport);
	const TArray<FAssetData>& GetPackagesToExport() const;
	const TSet<ETargetPlatform>& GetPlatforms() const;

	void UpdatePlatforms();

public:
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Config|Platform")
	bool bEditor;

	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Config|Platform")
	bool bWindows;

	UPROPERTY(config, VisibleAnywhere, BlueprintReadWrite, Category = "Config|Platform")
	bool bAndroid;

	UPROPERTY(config, VisibleAnywhere, BlueprintReadWrite, Category = "Config|Platform")
	bool bIOS;

	UPROPERTY(config, VisibleAnywhere, BlueprintReadWrite, Category = "Config|Platform")
	bool bPS4;

	UPROPERTY(config, VisibleAnywhere, BlueprintReadWrite, Category = "Config|Platform")
	bool bXboxOne;

	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Config|Pak")
	bool bCompress;

	UPROPERTY(config, VisibleAnywhere, BlueprintReadOnly, Category = "Config")
	FString SavedDir;

	//UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "ExportFiles")
	//TArray<FFilePath> m_packagesToExport;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (DisplayThumbnail = "true"), Category = "ExportFiles")
	TArray<UObject*> ObjectsToExport;

private:
	TArray<FAssetData> m_packagesToExport;
	TSet<ETargetPlatform> m_platforms;

private:
	FString m_cfgFile;
};
