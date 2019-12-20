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
		bool bIsClassType;
		FAssetData AssetData = FAutomationEditorCommonUtils::GetAssetDataFromPackagePath(PackageFilename);
		TWeakObjectPtr<UClass> ThumbnailClass = MakeWeakObjectPtr(const_cast<UClass*>(FClassIconFinder::GetIconClassForAssetData(AssetData,&bIsClassType)));
		const FName DefaultThumbnail = (bIsClassType) ? NAME_None : FName(*FString::Printf(TEXT("ClassThumbnail.%s"), *AssetData.AssetClass.ToString()));
		
		const FSlateBrush * ThumbnailBrush = FClassIconFinder::FindThumbnailForClass(ThumbnailClass.Get(), DefaultThumbnail);
		//ShowImage->SetImage(ThumbnailBrush);
		const FSlateBrush * IconBrush = FSlateIconFinder::FindIconBrushForClass(ThumbnailClass.Get());
		ShowImage->SetImage(IconBrush);


		/*TSet<FName> ObjectFullNames;
		FThumbnailMap ThumbnailMap;

		FName ObjectFullName = FName(TEXT("StaticMesh /Game/CastlePack/Meshes/SM_Mine_lvl0.SM_Mine_lvl0"));
		ObjectFullNames.Add(ObjectFullName);

		ThumbnailTools::LoadThumbnailsFromPackage(PackageFilename, ObjectFullNames, ThumbnailMap);

		const FObjectThumbnail* ThumbnailPtr = ThumbnailMap.Find(ObjectFullName);
		if (ThumbnailPtr)
		{
			const FObjectThumbnail& ObjectThumbnail = *ThumbnailPtr;
			TSharedPtr<FSlateDynamicImageBrush> DynamicBrush = FSlateDynamicImageBrush::CreateWithImageData(ObjectFullName,FVector2D(ObjectThumbnail.GetImageWidth(),ObjectThumbnail.GetImageHeight()),ObjectThumbnail.AccessImageData());
			ShowImage->SetImage(DynamicBrush.Get());
		}*/
	}
	return
		SNew(SBox)
		.WidthOverride(100)
		.HeightOverride(100)
		[
			SNew(SBorder)
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