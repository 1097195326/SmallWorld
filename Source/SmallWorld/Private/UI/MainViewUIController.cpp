#include "MainViewUIController.h"



TSharedPtr<SWidget> MainViewUIController::MakeTopLeftWidget()
{
	return 
	SNew(SBox)
		.WidthOverride(500)
		.HeightOverride(500)
		[
			SNew(SBorder)
			//.BorderBackgroundColor(FLinearColor(1,0,0,0.3f))
		.BorderBackgroundColor(FGameStyle::Get().GetColor("Color.FFFFC266"))
			.BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
		];
}
TSharedPtr<SWidget>	MainViewUIController::MakeTopCenterWidget()
{
	return
		SNew(SBox)
		.WidthOverride(500)
		.HeightOverride(500)
		[
			SNew(SBorder)
			//.BorderBackgroundColor(FLinearColor(1,0,0,0.3f))
		.BorderBackgroundColor(FGameStyle::Get().GetColor("Color.FFFFC266"))
		.BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
		];
}
TSharedPtr<SWidget>	MainViewUIController::MakeTopRightWidget()
{
	return
		SNew(SBox)
		.WidthOverride(500)
		.HeightOverride(500)
		[
			SNew(SBorder)
			//.BorderBackgroundColor(FLinearColor(1,0,0,0.3f))
		.BorderBackgroundColor(FGameStyle::Get().GetColor("Color.FFFFC266"))
		.BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
		];
}
TSharedPtr<SWidget>	MainViewUIController::MakeMiddleLeftWidget()
{
	TSharedPtr<SImage> ShowImage = SNew(SImage);
	FString  PackageName = TEXT("/Game/CastlePack/Meshes/SM_Mine_lvl0");
	FString PackageFilename;
	if (FPackageName::DoesPackageExist(PackageName, NULL, &PackageFilename))
	{
		FAssetData AssetData = FAutomationEditorCommonUtils::GetAssetDataFromPackagePath(PackageFilename);
		FName ObjectFullName = FName(*AssetData.GetFullName());
		
		FThumbnailMap ThumbnailMap;

		const FObjectThumbnail* ThumbnailPtr = ThumbnailTools::FindCachedThumbnail(ObjectFullName.ToString());
		if (!ThumbnailPtr)
		{
			TSet<FName> ObjectFullNames;
			ObjectFullNames.Add(ObjectFullName);
			ThumbnailTools::LoadThumbnailsFromPackage(PackageFilename, ObjectFullNames, ThumbnailMap);
			ThumbnailPtr = ThumbnailMap.Find(ObjectFullName);
		}
		if (ThumbnailPtr)
		{
			static TSharedPtr<FSlateDynamicImageBrush> DynamicBrush = FSlateDynamicImageBrush::CreateWithImageData(
				ObjectFullName,
				FVector2D(ThumbnailPtr->GetImageWidth(), ThumbnailPtr->GetImageHeight()),
				ThumbnailPtr->GetUncompressedImageData());
			if (DynamicBrush.IsValid() && ThumbnailPtr->GetUncompressedImageData().Num() > 0)
			{
				ShowImage->SetImage(DynamicBrush.Get());
			}
		}
	}
	return
		SNew(SBox)
		.WidthOverride(100)
		.HeightOverride(100)
		[
			SNew(SBorder)
			.Padding(0)
			//.BorderBackgroundColor(FLinearColor(1,0,0,0.3f))
			.BorderBackgroundColor(FGameStyle::Get().GetColor("Color.FFFFC266"))
			.BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
			[
				ShowImage.ToSharedRef()
			]
		];
	
}
TSharedPtr<SWidget>		MainViewUIController::MakeMiddleCenterWidget()
{
	return
		SNew(SBox)
		.WidthOverride(100)
		.HeightOverride(100)
		[
			SNew(SBorder)
			//.BorderBackgroundColor(FLinearColor(1,0,0,0.3f))
		.BorderBackgroundColor(FGameStyle::Get().GetColor("Color.FFFFC266"))
		.BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
		];
}
TSharedPtr<SWidget>	MainViewUIController::MakeMiddleRightWidget()
{
	return
		SNew(SBox)
		.WidthOverride(100)
		.HeightOverride(100)
		[
			SNew(SBorder)
			//.BorderBackgroundColor(FLinearColor(1,0,0,0.3f))
		.BorderBackgroundColor(FGameStyle::Get().GetColor("Color.FFFFC266"))
		.BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
		];
}
TSharedPtr<SWidget>	MainViewUIController::MakeBottomLeftWidget()
{
	return
		SNew(SBox)
		.WidthOverride(500)
		.HeightOverride(500)
		[
			SNew(SBorder)
			//.BorderBackgroundColor(FLinearColor(1,0,0,0.3f))
		.BorderBackgroundColor(FGameStyle::Get().GetColor("Color.FFFFC266"))
		.BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
		];
}
TSharedPtr<SWidget>	MainViewUIController::MakeBottomCenterWidget()
{
	return
		SNew(SBox)
		.WidthOverride(500)
		.HeightOverride(500)
		[
			SNew(SBorder)
			//.BorderBackgroundColor(FLinearColor(1,0,0,0.3f))
		.BorderBackgroundColor(FGameStyle::Get().GetColor("Color.FFFFC266"))
		.BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
		];
}
TSharedPtr<SWidget>	MainViewUIController::MakeBottomRightWidget()
{
	return
		SNew(SBox)
		.WidthOverride(500)
		.HeightOverride(500)
		[
			SNew(SBorder)
			//.BorderBackgroundColor(FLinearColor(1,0,0,0.3f))
		.BorderBackgroundColor(FGameStyle::Get().GetColor("Color.FFFFC266"))
		.BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
		];
}