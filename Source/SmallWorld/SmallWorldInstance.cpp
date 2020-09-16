#include "SmallWorldInstance.h"
#include "GameWorld.h"
#include "TimerManager.h"

#include "UI/SlateStyles/GameStyle.h"
#include "GameDataManager.h"

// exec
#include "Engine/WorldComposition.h"
#include "Misc/FileHelper.h"
#include "Misc/MessageDialog.h"
#include "HAL/FileManager.h"
#include "Misc/ScopedSlowTask.h"
#include "LevelUtils.h"
#include "AssetRegistryModule.h"
#include "Internationalization/Internationalization.h"

USmallWorldInstance::FOnPreSaveWorld		USmallWorldInstance::PreSaveWorld;
USmallWorldInstance::FOnPostSaveWorld		USmallWorldInstance::PostSaveWorld;

class FSaveErrorOutputDevice : public FOutputDevice
{
public:
	virtual void Serialize(const TCHAR* InData, ELogVerbosity::Type Verbosity, const class FName& Category) override
	{
		if (Verbosity == ELogVerbosity::Error || Verbosity == ELogVerbosity::Warning)
		{
			EMessageSeverity::Type Severity;
			if (Verbosity == ELogVerbosity::Error)
			{
				Severity = EMessageSeverity::Error;
			}
			else
			{
				Severity = EMessageSeverity::Warning;
			}
			ErrorMessages.Add(FTokenizedMessage::Create(Severity, FText::FromName(InData)));
		}
	}

	virtual void Flush() override
	{
		if (ErrorMessages.Num() > 0)
		{
			FMessageLog EditorErrors("EditorErrors");
			EditorErrors.NewPage(FText::FromString("Save Output"));
			EditorErrors.AddMessages(ErrorMessages);
			EditorErrors.Open();
			ErrorMessages.Empty();
		}
	}

private:
	// Holds the errors for the message log.
	TArray< TSharedRef< FTokenizedMessage > > ErrorMessages;
};


USmallWorldInstance::USmallWorldInstance()
{
	

}
void USmallWorldInstance::On_Init()
{
	m_Instance = this;
	

	FGameStyle::Startup();

	GameDataManager::GetInstance()->LoadData();

}
void USmallWorldInstance::On_Start()
{
	GetTimerManager().SetTimer(GameUpdateHandle, this, &USmallWorldInstance::UpdateGame, 0.1f, true);

}
void USmallWorldInstance::On_Delete()
{

}
void USmallWorldInstance::UpdateGame()
{
	GameWorld::GetInstance()->Update();

}
void USmallWorldInstance::ApplicationWillEnterBackground()
{

}
void USmallWorldInstance::ApplicationHasEnteredForeground()
{

}
// ------------
//FString::Printf( TEXT("OBJ SAVEPACKAGE PACKAGE=\"%s\" FILE=\"%s\" SILENT=true AUTOSAVING=%s KEEPDIRTY=%s")
bool USmallWorldInstance::Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Out)
{
	if (Super::Exec(InWorld, Cmd, Out))
	{
		return true;
	}
	else if (FParse::Command(&Cmd, TEXT("OBJ")))
	{
		return Exec_Obj(Cmd, Out);
	}

	return false;
}
bool USmallWorldInstance::Exec_Obj(const TCHAR* Str, FOutputDevice& Ar)
{
	if (FParse::Command(&Str, TEXT("EXPORT")))
	{
		return true;
	}
	else if (FParse::Command(&Str, TEXT("SavePackage")))
	{
		UPackage* Pkg;
		bool bWasSuccessful = true;

		FString TempFname;
		if (FParse::Value(Str, TEXT("FILE="), TempFname) && ParseObject<UPackage>(Str, TEXT("Package="), Pkg, NULL))
		{
			if (Pkg == nullptr || !CanSavePackage(Pkg))
			{
				return false;
			}
			bool bSilent = false;
			bool bAutosaving = false;
			bool bKeepDirty = false;
			FParse::Bool(Str, TEXT("SILENT="), bSilent);
			FParse::Bool(Str, TEXT("AUTOSAVING="), bAutosaving);
			FParse::Bool(Str, TEXT("KEEPDIRTY="), bKeepDirty);

			// Save the package.
			const bool bIsMapPackage = UWorld::FindWorldInPackage(Pkg) != nullptr;
			const FText SavingPackageText = (bIsMapPackage)
				? FText::Format(NSLOCTEXT("UnrealEd", "SavingMapf", "Saving map {0}"), FText::FromString(Pkg->GetName()))
				: FText::Format(NSLOCTEXT("UnrealEd", "SavingAssetf", "Saving asset {0}"), FText::FromString(Pkg->GetName()));

			FScopedSlowTask SlowTask(100, SavingPackageText, !bSilent);

			uint32 SaveFlags = bAutosaving ? SAVE_FromAutosave : SAVE_None;
			if (bKeepDirty)
			{
				SaveFlags |= SAVE_KeepDirty;
			}
			const bool bWarnOfLongFilename = !bAutosaving;
			bWasSuccessful = SavePackage(Pkg, NULL, RF_Standalone, *TempFname, &Ar, NULL, false, bWarnOfLongFilename, SaveFlags);

		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("zhx:Missing filename"));
		}
		return bWasSuccessful;
	}
	else if (FParse::Command(&Str, TEXT("Rename")))
	{
		return true;
	}
	return false;
}
bool USmallWorldInstance::SaveMap(UWorld* InWorld, const FString& Filename)
{
	bool bLevelWasSaved = false;
	
	{
		const double SaveStartTime = FPlatformTime::Seconds();

		FString FinalFilename;
		bLevelWasSaved = SaveWorld(InWorld, &Filename,
			nullptr, nullptr,
			true, false,
			FinalFilename,
			false, false);

		// Track time spent saving map.
		UE_LOG(LogTemp, Log, TEXT("Saving map '%s' took %.3f"), *FPaths::GetBaseFilename(Filename), FPlatformTime::Seconds() - SaveStartTime);
	}

	return bLevelWasSaved;
}
bool USmallWorldInstance::SaveAsImplementation(UWorld* InWorld, const FString& DefaultFilename, const bool bAllowStreamingLevelRename, FString* OutSavedFilename)
{
	FString Filename = FPaths::GetCleanFilename(DefaultFilename);
	if (Filename.IsEmpty())
	{
		const FString DefaultName = TEXT("NewMap");
		FString PackageName;
		// Initial location is invalid (e.g. lies outside of the project): set location to /Game/Maps instead
		FString DefaultDirectory = FPaths::ProjectContentDir() / TEXT("Maps");
		FPackageName::TryConvertFilenameToLongPackageName(DefaultDirectory / DefaultName, PackageName);
		
		FString Name;
		FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools");
		AssetToolsModule.Get().CreateUniqueAssetName(PackageName, TEXT(""), PackageName, Name);

		Filename = FPaths::GetCleanFilename(FPackageName::LongPackageNameToFilename(PackageName));
	}

	bool bStatus = false;

	// Loop through until a valid filename is given or the user presses cancel
	bool bFilenameIsValid = false;

	FString SaveFilename;
	while (!bFilenameIsValid)
	{
		SaveFilename = FString();
		bool bSaveFileLocationSelected = false;

		FString DefaultPackagePath;
		FPackageName::TryConvertFilenameToLongPackageName(DefaultDirectory / Filename, DefaultPackagePath);

		FString PackageName;
		bSaveFileLocationSelected = OpenSaveAsDialog(
			UWorld::StaticClass(),
			FPackageName::GetLongPackagePath(DefaultPackagePath),
			FPaths::GetBaseFilename(Filename),
			PackageName);

		if (bSaveFileLocationSelected)
		{
			SaveFilename = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetMapPackageExtension());

			FText ErrorMessage;
			bFilenameIsValid = FEditorFileUtils::IsValidMapFilename(SaveFilename, ErrorMessage);

			if (bFilenameIsValid)
			{
				// If there is an existing world in memory that shares this name unload it now to prepare for overwrite.
				// Don't do this if we are using save as to overwrite the current level since it will just save naturally.
				const FString NewPackageName = FPackageName::FilenameToLongPackageName(SaveFilename);
				UPackage* ExistingPackage = FindPackage(nullptr, *NewPackageName);
				if (ExistingPackage && ExistingPackage != InWorld->GetOutermost())
				{
					bFilenameIsValid = FEditorFileUtils::AttemptUnloadInactiveWorldPackage(ExistingPackage, ErrorMessage);
				}
			}

			if (!bFilenameIsValid)
			{
				// Start the loop over, prompting for save again
				const FText DisplayFilename = FText::FromString(IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*SaveFilename));
				FFormatNamedArguments Arguments;
				Arguments.Add(TEXT("Filename"), DisplayFilename);
				Arguments.Add(TEXT("LineTerminators"), FText::FromString(LINE_TERMINATOR LINE_TERMINATOR));
				Arguments.Add(TEXT("ErrorMessage"), ErrorMessage);
				const FText DisplayMessage = FText::Format(NSLOCTEXT("SaveAsImplementation", "InvalidMapName", "Failed to save map {Filename}{LineTerminators}{ErrorMessage}"), Arguments);
				FMessageDialog::Open(EAppMsgType::Ok, DisplayMessage);
				continue;
			}

			FEditorDirectories::Get().SetLastDirectory(ELastDirectory::LEVEL, FPaths::GetPath(SaveFilename));

			// Check to see if there are streaming level associated with the P map, and if so, we'll
			// prompt to rename those and fixup all of the named-references to levels in the maps.
			bool bCanRenameStreamingLevels = false;
			FString OldBaseLevelName, NewBaseLevelName;

			if (bAllowStreamingLevelRename)
			{
				const FString OldLevelName = FPaths::GetBaseFilename(Filename);
				const FString NewLevelName = FPaths::GetBaseFilename(SaveFilename);

				// The old and new level names must have a common suffix.  We'll detect that now.
				int32 NumSuffixChars = 0;
				{
					for (int32 CharsFromEndIndex = 0; ; ++CharsFromEndIndex)
					{
						const int32 OldLevelNameCharIndex = (OldLevelName.Len() - 1) - CharsFromEndIndex;
						const int32 NewLevelNameCharIndex = (NewLevelName.Len() - 1) - CharsFromEndIndex;

						if (OldLevelNameCharIndex <= 0 || NewLevelNameCharIndex <= 0)
						{
							// We've processed all characters in at least one of the strings!
							break;
						}

						if (FChar::ToUpper(OldLevelName[OldLevelNameCharIndex]) != FChar::ToUpper(NewLevelName[NewLevelNameCharIndex]))
						{
							// Characters don't match.  We have the common suffix now.
							break;
						}

						// We have another common character in the suffix!
						++NumSuffixChars;
					}

				}


				// We can only proceed if we found a common suffix
				if (NumSuffixChars > 0)
				{
					FString CommonSuffix = NewLevelName.Right(NumSuffixChars);

					OldBaseLevelName = OldLevelName.Left(OldLevelName.Len() - CommonSuffix.Len());
					NewBaseLevelName = NewLevelName.Left(NewLevelName.Len() - CommonSuffix.Len());


					// OK, make sure this is really the persistent level
					if (InWorld->PersistentLevel->IsPersistentLevel())
					{
						// Check to see if we actually have anything to rename
						bool bAnythingToRename = false;
						{
							// Check for contained streaming levels
							for (ULevelStreaming* CurStreamingLevel : InWorld->GetStreamingLevels())
							{
								if (CurStreamingLevel)
								{
									// Update the package name
									FString PackageNameToRename = CurStreamingLevel->GetWorldAssetPackageName();
									if (RenameStreamingLevel(PackageNameToRename, OldBaseLevelName, NewBaseLevelName))
									{
										bAnythingToRename = true;
									}
								}
							}
						}

						if (bAnythingToRename)
						{
							// OK, we can go ahead and rename levels
							bCanRenameStreamingLevels = true;
						}
					}
				}
			}

			{
				// Save the level
				bStatus = FEditorFileUtils::SaveMap(InWorld, SaveFilename);
			}
		}
		else
		{
			// User canceled the save dialog, do not prompt again.
			break;
		}

	}

	// Restore autosaving to its previous state.
	LoadingSavingSettings->bAutoSaveEnable = bOldAutoSaveState;

	// Update SCC state
	ISourceControlModule::Get().QueueStatusUpdate(InWorld->GetOutermost());

	if (bStatus && OutSavedFilename)
	{
		*OutSavedFilename = SaveFilename;
	}

	return bStatus;
}
bool USmallWorldInstance::SaveWorld(UWorld* World,
	const FString* ForceFilename,
	const TCHAR* OverridePath,
	const TCHAR* FilenamePrefix,
	bool bRenamePackageToFile,
	bool bCheckDirty,
	FString& FinalFilename,
	bool bAutosaving,
	bool bPIESaving)
{
	// SaveWorld not reentrant - check that we are not already in the process of saving here (for example, via autosave)
	static bool bIsReentrant = false;
	if (bIsReentrant)
	{
		return false;
	}

	TGuardValue<bool> ReentrantGuard(bIsReentrant, true);

	if (!World)
	{
		//FinalFilename = LOCTEXT("FilenameUnavailable", "Filename Not available!").ToString();
		return false;
	}

	UPackage* Package = Cast<UPackage>(World->GetOuter());
	if (!Package)
	{
		//FinalFilename = LOCTEXT("FilenameUnavailableInvalidOuter", "Filename Not available. Outer package invalid!").ToString();
		return false;
	}

	// Don't save if the world doesn't need saving.
	if (bCheckDirty && !Package->IsDirty())
	{
		//FinalFilename = LOCTEXT("FilenameUnavailableNotDirty", "Filename Not available. Package not dirty.").ToString();
		return false;
	}

	FString PackageName = Package->GetName();

	FString	ExistingFilename;
	FString	Path;
	FString	CleanFilename;

	// Does a filename already exist for this package?
	const bool bPackageExists = DoesPackageExist(Package, &ExistingFilename);

	if (ForceFilename)
	{
		Path = FPaths::GetPath(*ForceFilename);
		CleanFilename = FPaths::GetCleanFilename(*ForceFilename);
	}
	else if (bPackageExists)
	{
		if (bPIESaving && FCString::Stristr(*ExistingFilename, *FPackageName::GetMapPackageExtension()) == NULL)
		{
			// If package exists, but doesn't feature the default extension, it will not load when launched,
			// Change the extension of the map to the default for the auto-save
			Path = GetAutoSaveDir();
			CleanFilename = FPackageName::GetLongPackageAssetName(PackageName) + FPackageName::GetMapPackageExtension();
		}
		else
		{
			// We're not forcing a filename, so go with the filename that exists.
			Path = FPaths::GetPath(ExistingFilename);
			CleanFilename = FPaths::GetCleanFilename(ExistingFilename);
		}
	}
	else if (!bAutosaving && FPackageName::IsValidLongPackageName(PackageName, false))
	{
		// If the package is made with a path in a non-read-only root, save it there
		const FString ImplicitFilename = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetMapPackageExtension());
		Path = FPaths::GetPath(ImplicitFilename);
		CleanFilename = FPaths::GetCleanFilename(ImplicitFilename);
	}
	else
	{
		// No package filename exists and none was specified, so save the package in the autosaves folder.
		Path = GetAutoSaveDir();
		CleanFilename = FPackageName::GetLongPackageAssetName(PackageName) + FPackageName::GetMapPackageExtension();
	}

	// Optionally override path.
	if (OverridePath)
	{
		FinalFilename = FString(OverridePath) + TEXT("/");
	}
	else
	{
		FinalFilename = Path + TEXT("/");
	}

	// Apply optional filename prefix.
	if (FilenamePrefix)
	{
		FinalFilename += FString(FilenamePrefix);
	}

	// Munge remaining clean filename minus path + extension with path and optional prefix.
	FinalFilename += CleanFilename;

	// Prepare the new package name
	FString NewPackageName;
	if (!FPackageName::TryConvertFilenameToLongPackageName(FinalFilename, NewPackageName))
	{
		FMessageDialog::Open(EAppMsgType::Ok, FText::Format(NSLOCTEXT("Editor", "SaveWorld_BadFilename", "Failed to save the map. The filename '{0}' is not within the game or engine content folders found in '{1}'."), FText::FromString(FinalFilename), FText::FromString(FPaths::RootDir())));
		return false;
	}

	// Before doing any work, check to see if 1) the package name is in use by another object, 2) the world object can be renamed if necessary; and 3) the file is writable.
	bool bSuccess = false;

	const FString OriginalWorldName = World->GetName();
	const FString OriginalPackageName = Package->GetName();
	const FString NewWorldAssetName = FPackageName::GetLongPackageAssetName(NewPackageName);
	bool bValidWorldName = true;
	bool bPackageNeedsRename = false;
	bool bWorldNeedsRename = false;

	if (bRenamePackageToFile)
	{
		// Rename the world package if needed
		if (Package->GetName() != NewPackageName)
		{
			bValidWorldName = Package->Rename(*NewPackageName, NULL, REN_Test);
			if (bValidWorldName)
			{
				bPackageNeedsRename = true;
			}
		}

		if (bValidWorldName)
		{
			// Rename the world if the package changed
			if (World->GetName() != NewWorldAssetName)
			{
				bValidWorldName = World->Rename(*NewWorldAssetName, NULL, REN_Test);
				if (bValidWorldName)
				{
					bWorldNeedsRename = true;
				}
			}
		}
	}

	if (!bValidWorldName)
	{
		FMessageDialog::Open(EAppMsgType::Ok, NSLOCTEXT("UnrealEd", "Error_LevelNameExists", "A level with that name already exists. Please choose another name."));
	}
	else if (IFileManager::Get().IsReadOnly(*FinalFilename))
	{
		FMessageDialog::Open(EAppMsgType::Ok, FText::Format(NSLOCTEXT("UnrealEd", "PackageFileIsReadOnly", "Unable to save package to {0} because the file is read-only!"), FText::FromString(FinalFilename)));
	}
	else
	{
		// Save the world package after doing optional garbage collection.
		//const FScopedBusyCursor BusyCursor;

		FFormatNamedArguments Args;
		Args.Add(TEXT("MapFilename"), FText::FromString(FPaths::GetCleanFilename(FinalFilename)));

		FScopedSlowTask SlowTask(100, FText::Format(NSLOCTEXT("UnrealEd", "SavingMap_F", "Saving map: {MapFilename}..."), Args));
		SlowTask.MakeDialog(true);

		SlowTask.EnterProgressFrame(25);

		FSoftObjectPath OldPath(World);
		bool bAddedAssetPathRedirection = false;

		// Rename the package and the object, as necessary
		UWorld* DuplicatedWorld = nullptr;
		
		// Mark package as fully loaded, this is usually set implicitly by calling IsFullyLoaded before saving, but that path can get skipped for levels
		Package->MarkAsFullyLoaded();

		SlowTask.EnterProgressFrame(50);

		// Save package.
		{
			const FString AutoSavingString = (bAutosaving || bPIESaving) ? TEXT("true") : TEXT("false");
			const FString KeepDirtyString = bPIESaving ? TEXT("true") : TEXT("false");
			FSaveErrorOutputDevice SaveErrors;

			bSuccess = Exec(NULL, *FString::Printf(TEXT("OBJ SAVEPACKAGE PACKAGE=\"%s\" FILE=\"%s\" SILENT=true AUTOSAVING=%s KEEPDIRTY=%s"), *Package->GetName(), *FinalFilename, *AutoSavingString, *KeepDirtyString), SaveErrors);
			SaveErrors.Flush();
		}

		// @todo Autosaving should save build data as well
		if (bSuccess && !bAutosaving)
		{
			// Also save MapBuildData packages when saving the current level
			//FEditorFileUtils::SaveMapDataPackages(DuplicatedWorld ? DuplicatedWorld : World, bCheckDirty || bPIESaving);
		}

		SlowTask.EnterProgressFrame(25);

		// If the package save was not successful. Trash the duplicated world or rename back if the duplicate failed.
		if (bRenamePackageToFile && !bSuccess)
		{
			if (bPackageNeedsRename)
			{
				{
					Package->Rename(*OriginalPackageName, NULL, REN_NonTransactional);

					if (bWorldNeedsRename)
					{
						World->Rename(*OriginalWorldName, NULL, REN_NonTransactional);
					}
				}
			}
		}
	}

	return bSuccess;
}
bool USmallWorldInstance::SavePackage(UPackage* InOuter, UObject* InBase, EObjectFlags TopLevelFlags, const TCHAR* Filename, FOutputDevice* Error /* = GError */, FLinkerNull* Conform /* = NULL */, bool bForceByteSwapping /* = false */, bool bWarnOfLongFilename /* = true */, uint32 SaveFlags /* = SAVE_None */, const class ITargetPlatform* TargetPlatform /* = NULL */, const FDateTime& FinalTimeStamp /* = FDateTime::MinValue() */, bool bSlowTask /* = true */)
{
	// Workaround to avoid function signature change while keeping both bool and ESavePackageResult versions of SavePackage
	const FSavePackageResultStruct Result = Save(InOuter, InBase, TopLevelFlags, Filename, Error, Conform, bForceByteSwapping,
		bWarnOfLongFilename, SaveFlags, TargetPlatform, FinalTimeStamp, bSlowTask);
	return Result == ESavePackageResult::Success;
}
FSavePackageResultStruct USmallWorldInstance::Save(UPackage* InOuter, UObject* InBase, EObjectFlags TopLevelFlags, const TCHAR* Filename, FOutputDevice* Error /* = GError */, FLinkerNull* Conform /* = NULL */, bool bForceByteSwapping /* = false */, bool bWarnOfLongFilename /* = true */, uint32 SaveFlags /* = SAVE_None */, const class ITargetPlatform* TargetPlatform /* = NULL */, const FDateTime& FinalTimeStamp /* = FDateTime::MinValue() */, bool bSlowTask /* = true */, class FArchiveDiffMap* InOutDiffMap /* = nullptr */, FSavePackageContext* SavePackageContext /* = nullptr */)
{
	FScopedSlowTask SlowTask(100, FText(), bSlowTask);

	UObject* Base = InBase;
	if (!Base && InOuter && InOuter->HasAnyPackageFlags(PKG_ContainsMap))
	{
		Base = UWorld::FindWorldInPackage(InOuter);
	}

	// Record the package flags before OnPreSaveWorld. They will be used in OnPostSaveWorld.
	const uint32 OriginalPackageFlags = (InOuter ? InOuter->GetPackageFlags() : 0);

	SlowTask.EnterProgressFrame(10);

	UWorld* World = Cast<UWorld>(Base);
	bool bInitializedPhysicsSceneForSave = false;
	bool bForceInitializedWorld = false;
	const bool bSavingConcurrent = !!(SaveFlags & ESaveFlags::SAVE_Concurrent);

	UWorld *OriginalOwningWorld = nullptr;
	if (World)
	{
		if (!bSavingConcurrent)
		{
			bInitializedPhysicsSceneForSave = InitializePhysicsSceneForSaveIfNecessary(World, bForceInitializedWorld);

			OnPreSaveWorld(SaveFlags, World);
		}

		OriginalOwningWorld = World->PersistentLevel->OwningWorld;
		World->PersistentLevel->OwningWorld = World;
	}

	SlowTask.EnterProgressFrame(70);

	UPackage::PreSavePackageEvent.Broadcast(InOuter);
	FSavePackageResultStruct Result = UPackage::Save(InOuter, Base, TopLevelFlags, Filename, Error, Conform, bForceByteSwapping, bWarnOfLongFilename, SaveFlags, TargetPlatform, FinalTimeStamp, bSlowTask, InOutDiffMap, SavePackageContext);

	SlowTask.EnterProgressFrame(10);

	if (World)
	{
		if (OriginalOwningWorld)
		{
			World->PersistentLevel->OwningWorld = OriginalOwningWorld;
		}

		if (!bSavingConcurrent)
		{
			OnPostSaveWorld(SaveFlags, World, OriginalPackageFlags, Result == ESavePackageResult::Success);

			if (bInitializedPhysicsSceneForSave)
			{
				CleanupPhysicsSceneThatWasInitializedForSave(World, bForceInitializedWorld);
			}

			if (Result == ESavePackageResult::Success) // Package saved successfully?
			{
				// Rerunning construction scripts may have made it dirty again
				InOuter->SetDirtyFlag(false);
			}
		}
	}

	return Result;
}
void USmallWorldInstance::OnPreSaveWorld(uint32 SaveFlags, UWorld* World)
{
	if (!ensure(World))
	{
		return;
	}

	check(World->PersistentLevel);

	// Pre save world event
	USmallWorldInstance::PreSaveWorld.Broadcast(SaveFlags, World);

	// Update cull distance volumes (and associated primitives).
	World->UpdateCullDistanceVolumes();

	if (!IsRunningCommandlet())
	{
		const bool bAutosaveOrPIE = (SaveFlags & SAVE_FromAutosave) != 0;
		if (bAutosaveOrPIE)
		{
			// Temporarily flag packages saved under a PIE filename as PKG_PlayInEditor for serialization so loading
			// them will have the flag set. We need to undo this as the object flagged isn't actually the PIE package, 
			// but rather only the loaded one will be.
			// PIE prefix detected, mark package.
			if (World->GetName().StartsWith(PLAYWORLD_PACKAGE_PREFIX))
			{
				World->GetOutermost()->SetPackageFlags(PKG_PlayInEditor);
			}
		}
		else
		{
			// Normal non-pie and non-autosave codepath
			//FWorldContext &EditorContext = GetEditorWorldContext();

			//// Check that this world is GWorld to avoid stomping on the saved views of sub-levels.
			//if (World == EditorContext.World())
			//{
			//	if (FModuleManager::Get().IsModuleLoaded("LevelEditor"))
			//	{
			//		FLevelEditorModule& LevelEditor = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");

			//		// Notify slate level editors of the map change
			//		LevelEditor.BroadcastMapChanged(World, EMapChangeType::SaveMap);
			//	}
			//}

			// Shrink model and clean up deleted actors.
			// Don't do this when autosaving or PIE saving so that actor adds can still undo.
			World->ShrinkLevel();

			{
				FScopedSlowTask SlowTask(0, FText::Format(NSLOCTEXT("UnrealEd", "SavingMapStatus_CollectingGarbage", "Saving map: {0}... (Collecting garbage)"), FText::FromString(World->GetName())));
				// NULL empty or "invalid" entries (e.g. IsPendingKill()) in actors array.
				CollectGarbage(GARBAGE_COLLECTION_KEEPFLAGS);
			}

			// Compact and sort actors array to remove empty entries.
			// Don't do this when autosaving or PIE saving so that actor adds can still undo.
			World->PersistentLevel->SortActorList();
		}
	}

	// Move level position closer to world origin
	UWorld* OwningWorld = World->PersistentLevel->OwningWorld;
	if (OwningWorld->WorldComposition)
	{
		OwningWorld->WorldComposition->OnLevelPreSave(World->PersistentLevel);
	}

	// If we can get the streaming level, we should remove the editor transform before saving
	ULevelStreaming* LevelStreaming = FLevelUtils::FindStreamingLevel(World->PersistentLevel);
	if (LevelStreaming && World->PersistentLevel->bAlreadyMovedActors)
	{
		FLevelUtils::RemoveEditorTransform(LevelStreaming);
	}

	// Make sure the public and standalone flags are set on this world to allow it to work properly with the editor
	World->SetFlags(RF_Public | RF_Standalone);
}
void USmallWorldInstance::OnPostSaveWorld(uint32 SaveFlags, UWorld* World, uint32 OriginalPackageFlags, bool bSuccess)
{
	if (!ensure(World))
	{
		return;
	}

	if (!IsRunningCommandlet())
	{
		UPackage* WorldPackage = World->GetOutermost();
		const bool bAutosaveOrPIE = (SaveFlags & SAVE_FromAutosave) != 0;
		if (bAutosaveOrPIE)
		{
			// Restore original value of PKG_PlayInEditor if we changed it during PIE saving
			const bool bOriginallyPIE = (OriginalPackageFlags & PKG_PlayInEditor) != 0;
			const bool bCurrentlyPIE = (WorldPackage->HasAnyPackageFlags(PKG_PlayInEditor));
			if (!bOriginallyPIE && bCurrentlyPIE)
			{
				WorldPackage->ClearPackageFlags(PKG_PlayInEditor);
			}
		}
		else
		{
			//// Normal non-pie and non-autosave codepath
			//FWorldContext &EditorContext = GetEditorWorldContext();

			//const bool bIsPersistentLevel = (World == EditorContext.World());
			//if (bSuccess)
			//{
			//	// Put the map into the MRU and mark it as not dirty.

			//	if (bIsPersistentLevel)
			//	{
			//		// Set the map filename.
			//		const FString Filename = FPackageName::LongPackageNameToFilename(WorldPackage->GetName(), FPackageName::GetMapPackageExtension());
			//		FEditorFileUtils::RegisterLevelFilename(World, Filename);

			//		WorldPackage->SetDirtyFlag(false);

			//		// Update the editor's MRU level list if we were asked to do that for this level
			//		IMainFrameModule& MainFrameModule = FModuleManager::LoadModuleChecked<IMainFrameModule>("MainFrame");

			//		if (MainFrameModule.GetMRUFavoritesList())
			//		{
			//			MainFrameModule.GetMRUFavoritesList()->AddMRUItem(WorldPackage->GetName());
			//		}

			//		FEditorDirectories::Get().SetLastDirectory(ELastDirectory::UNR, FPaths::GetPath(Filename)); // Save path as default for next time.
			//	}

			//	// We saved the map, so unless there are any other dirty levels, go ahead and reset the autosave timer
			//	if (GUnrealEd && !GUnrealEd->AnyWorldsAreDirty(World))
			//	{
			//		GUnrealEd->GetPackageAutoSaver().ResetAutoSaveTimer();
			//	}
			//}

			//if (bIsPersistentLevel)
			//{
			//	//ResetTransaction(NSLOCTEXT("UnrealEd", "MapSaved", "Map Saved"));
			//	FPlatformProcess::SetCurrentWorkingDirectoryToBaseDir();
			//}
		}
	}

	// Restore level original position
	UWorld* OwningWorld = World->PersistentLevel->OwningWorld;
	if (OwningWorld->WorldComposition)
	{
		OwningWorld->WorldComposition->OnLevelPostSave(World->PersistentLevel);
	}

	// If got the streaming level, we should re-apply the editor transform after saving
	ULevelStreaming* LevelStreaming = FLevelUtils::FindStreamingLevel(World->PersistentLevel);
	if (LevelStreaming && World->PersistentLevel->bAlreadyMovedActors)
	{
		FLevelUtils::ApplyEditorTransform(LevelStreaming);
	}

	// Post save world event
	USmallWorldInstance::PostSaveWorld.Broadcast(SaveFlags, World, bSuccess);
}
bool USmallWorldInstance::CanSavePackage(UPackage* PackageToSave)
{
	bool bTemRes = true;
	const FString & PackageName = PackageToSave->GetName();
	if (FPackageName::IsValidLongPackageName(PackageName, /*bIncludeReadOnlyRoots=*/false))
	{
		// Test for write permission in the folder the package is in by creating a temp file and writing to it.
		// This isn't exactly the same as testing the package file for write permission, but we can not test that without directly writing to the file.
		FString BasePackageFileName = FPackageName::LongPackageNameToFilename(PackageName);
		FString TempPackageFileName = BasePackageFileName;

		// Make sure the temp file we are writing does not already exist by appending a numbered suffix
		const int32 MaxSuffix = 32;
		bool bCanTestPermission = false;
		for (int32 SuffixIdx = 0; SuffixIdx < MaxSuffix; ++SuffixIdx)
		{
			TempPackageFileName = BasePackageFileName + FString::Printf(TEXT(".tmp%d"), SuffixIdx);
			if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*TempPackageFileName))
			{
				// Found a file that is not already in use
				bCanTestPermission = true;
				break;
			}
		}

		// If we actually found a file to test permission, test it now.
		if (bCanTestPermission)
		{
			bool bHasWritePermission = FFileHelper::SaveStringToFile(TEXT("Write Test"), *TempPackageFileName);
			if (bHasWritePermission)
			{
				// We can successfully write to the folder containing the package.
				// Delete the temp file.
				IFileManager::Get().Delete(*TempPackageFileName);
			}
			else
			{
				// We may not write to the specified location. Warn the user that he will not be able to write to this file.
				bTemRes = false;
			}
		}
		else
		{
			// Failed to find a proper file to test permission...
		}
	}
	return bTemRes;
}
bool USmallWorldInstance::InitializePhysicsSceneForSaveIfNecessary(UWorld* World, bool &bOutForceInitialized)
{
	// We need a physics scene at save time in case code does traces during onsave events.
	bool bHasPhysicsScene = false;

	// First check if our owning world has a physics scene
	if (World->PersistentLevel && World->PersistentLevel->OwningWorld)
	{
		bHasPhysicsScene = (World->PersistentLevel->OwningWorld->GetPhysicsScene() != nullptr);
	}

	// If we didn't already find a physics scene in our owning world, maybe we personally have our own.
	if (!bHasPhysicsScene)
	{
		bHasPhysicsScene = (World->GetPhysicsScene() != nullptr);
	}


	// If we didn't find any physics scene we will synthesize one and remove it after save
	if (!bHasPhysicsScene)
	{
		// Clear world components first so that UpdateWorldComponents below properly adds them all to the physics scene
		World->ClearWorldComponents();

		if (World->bIsWorldInitialized)
		{
			// If we don't have a physics scene and the world was initialized without one (i.e. an inactive world) then we should create one here. We will remove it down below after the save
			World->CreatePhysicsScene();

			// Keep track of the force initialization so we can use the proper cleanup
			bOutForceInitialized = false;
		}
		else
		{
			// If we aren't already initialized, initialize now and create a physics scene. Don't create an FX system because it uses too much video memory for bulk operations
			World->InitWorld(GetEditorWorldInitializationValues().CreateFXSystem(false).CreatePhysicsScene(true));
			bOutForceInitialized = true;
		}

		// Update components now that a physics scene exists.
		World->UpdateWorldComponents(true, true);

		// Set this to true so we can clean up what we just did down below
		return true;
	}

	return false;
}
void USmallWorldInstance::CleanupPhysicsSceneThatWasInitializedForSave(UWorld* World, bool bForceInitialized)
{
	// Make sure we clean up the physics scene here. If we leave too many scenes in memory, undefined behavior occurs when locking a scene for read/write.
	World->ClearWorldComponents();

	if (bForceInitialized)
	{
		World->CleanupWorld(true, true, World);
	}

	World->SetPhysicsScene(nullptr);

#if WITH_PHYSX
	if (GPhysCommandHandler)
	{
		GPhysCommandHandler->Flush();
	}
#endif // WITH_PHYSX

	// Update components again in case it was a world without a physics scene but did have rendered components.
	World->UpdateWorldComponents(true, true);
}
UWorld::InitializationValues USmallWorldInstance::GetEditorWorldInitializationValues() const
{
	return UWorld::InitializationValues()
		.ShouldSimulatePhysics(false)
		.EnableTraceCollision(true);
}
bool USmallWorldInstance::DoesPackageExist(UPackage* Package, FString* OutFilename /* = nullptr */)
{
	// Test using asset registry to figure out existence
	IAssetRegistry& AssetRegistry = FAssetRegistryModule::GetRegistry();
	if (!AssetRegistry.IsLoadingAssets() || !GIsEditor)
	{
		TArray<FAssetData> Data;
		FAssetRegistryModule::GetRegistry().GetAssetsByPackageName(Package->GetFName(), Data, true);

		if (Data.Num() > 0 && OutFilename)
		{
			*OutFilename = FPackageName::LongPackageNameToFilename(Package->GetName(), Package->ContainsMap() ? FPackageName::GetMapPackageExtension() : FPackageName::GetAssetPackageExtension());
		}

		return Data.Num() > 0;
	}
	return FPackageName::DoesPackageExist(Package->GetName(), nullptr, OutFilename);
}
FString USmallWorldInstance::GetAutoSaveDir()
{
	return FPaths::ProjectSavedDir() / TEXT("Autosaves");
}