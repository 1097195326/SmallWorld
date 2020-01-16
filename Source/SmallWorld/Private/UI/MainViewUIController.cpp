#include "MainViewUIController.h"
#include "SHordePreviewWidget.h"

void MainViewUIController::InitControllerView()
{
	TopLeftSlot->AttachWidget(CreateUserView().ToSharedRef());
	BottomLeftSlot->AttachWidget(CreateToWorldButton().ToSharedRef());
	BottomRightSlot->AttachWidget(CreateBuildingButton().ToSharedRef());
}
TSharedPtr<SWidget> MainViewUIController::CreateUserView()
{
	TSharedPtr<SWidget> ResWidget = SNew(SHordePreviewWidget)
		.OnPowerClicked_Raw(this, &MainViewUIController::OnPowerClicked)
		.OnHeroClicked_Raw(this, &MainViewUIController::OnHeroClicked);
		
	return ResWidget;
}
TSharedPtr<SWidget>	MainViewUIController::CreateToWorldButton()
{
	TSharedPtr<SBox> ResBox = SNew(SBox)
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		.WidthOverride(128)
		.HeightOverride(128)
		[
			SNew(SButton)
			.ButtonStyle(&FGameStyle::Get().GetWidgetStyle<FButtonStyle>("MainView.Button.Map"))
		];
	return ResBox;
}
TSharedPtr<SWidget>	MainViewUIController::CreateBuildingButton()
{
	TSharedPtr<SBox> ResBox = SNew(SBox)
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		.WidthOverride(128)
		.HeightOverride(128)
		[
			SNew(SButton)
			.ButtonStyle(&FGameStyle::Get().GetWidgetStyle<FButtonStyle>("MainView.Button.Menu"))
		];
	return ResBox;
}
FReply MainViewUIController::OnPowerClicked()
{

	return FReply::Handled();
}
FReply MainViewUIController::OnHeroClicked()
{
	return FReply::Handled();
}
FReply MainViewUIController::OnMapClicked()
{

	return FReply::Handled();
}
FReply MainViewUIController::OnMenuClicked()
{
	return FReply::Handled();
}



// -----------------
TSharedPtr<SWidget>	MainViewUIController::TestWidget()
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
