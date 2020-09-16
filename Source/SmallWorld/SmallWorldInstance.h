#pragma once

#include "GAppInstance.h"
#include "SmallWorldInstance.generated.h"

#define  SWI USmallWorldInstance::GetInstance()

UCLASS()
class USmallWorldInstance : public UGAppInstance
{
	GENERATED_BODY()
		
private:
	FTimerHandle GameUpdateHandle;

	void UpdateGame();

public:
	USmallWorldInstance();

	virtual void On_Init() override;
	virtual void On_Start() override;
	virtual void On_Delete() override;

	//Begin Exec system
	/** delegate type for pre save world events ( uint32 SaveFlags, UWorld* World ) */
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPreSaveWorld, uint32, class UWorld*);
	/** delegate type for post save world events ( uint32 SaveFlags, UWorld* World, bool bSuccess ) */
	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnPostSaveWorld, uint32, class UWorld*, bool);

	/** Called before SaveWorld is processed */
	static FOnPreSaveWorld PreSaveWorld;
	/** Called after SaveWorld is processed */
	static FOnPostSaveWorld PostSaveWorld;

	virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Out = *GLog) override;
	bool Exec_Obj(const TCHAR* Str, FOutputDevice& Ar);

	bool SaveMap(UWorld* World, const FString& Filename);

	bool SaveAsImplementation(UWorld* InWorld, const FString& DefaultFilename, const bool bAllowStreamingLevelRename, FString* OutSavedFilename);
	
	bool SaveWorld(UWorld* World,
		const FString* ForceFilename,
		const TCHAR* OverridePath,
		const TCHAR* FilenamePrefix,
		bool bRenamePackageToFile,
		bool bCheckDirty,
		FString& FinalFilename,
		bool bAutosaving,
		bool bPIESaving);

	/** The editor wrapper for UPackage::SavePackage. Auto-adds files to source control when necessary */
	bool SavePackage(UPackage* InOuter, UObject* Base, EObjectFlags TopLevelFlags, const TCHAR* Filename,
		FOutputDevice* Error = GError, FLinkerNull* Conform = NULL, bool bForceByteSwapping = false, bool bWarnOfLongFilename = true,
		uint32 SaveFlags = SAVE_None, const class ITargetPlatform* TargetPlatform = NULL, const FDateTime& FinalTimeStamp = FDateTime::MinValue(), bool bSlowTask = true);

	/** The editor wrapper for UPackage::Save. Auto-adds files to source control when necessary */
	FSavePackageResultStruct Save(UPackage* InOuter, UObject* Base, EObjectFlags TopLevelFlags, const TCHAR* Filename,
		FOutputDevice* Error = GError, FLinkerNull* Conform = NULL, bool bForceByteSwapping = false, bool bWarnOfLongFilename = true,
		uint32 SaveFlags = SAVE_None, const class ITargetPlatform* TargetPlatform = NULL, const FDateTime& FinalTimeStamp = FDateTime::MinValue(),
		bool bSlowTask = true, class FArchiveDiffMap* InOutDiffMap = nullptr,
		FSavePackageContext* SavePackageContext = nullptr);

	/** Invoked before a UWorld is saved to update editor systems */
	void OnPreSaveWorld(uint32 SaveFlags, UWorld* World);

	/** Invoked after a UWorld is saved to update editor systems */
	void OnPostSaveWorld(uint32 SaveFlags, UWorld* World, uint32 OriginalPackageFlags, bool bSuccess);

	bool DoesPackageExist(UPackage* Package, FString* OutFilename = nullptr);

	bool InitializePhysicsSceneForSaveIfNecessary(UWorld* World, bool &bOutForceInitialized);
	void CleanupPhysicsSceneThatWasInitializedForSave(UWorld* World, bool bForceInitialized);

	bool CanSavePackage(UPackage* PackageToSave);
	UWorld::InitializationValues GetEditorWorldInitializationValues() const;
	FString GetAutoSaveDir();
	//End Exec System

	virtual    void ApplicationWillEnterBackground() override;
	virtual    void ApplicationHasEnteredForeground() override;
};