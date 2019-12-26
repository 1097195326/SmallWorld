#include "MainViewUIController.h"


void MainViewUIController::InitControllerView()
{
	TopLeftSlot->AttachWidget(CreateUserView().ToSharedRef());
	BottomLeftSlot->AttachWidget(CreateToWorldButton().ToSharedRef());
	BottomRightSlot->AttachWidget(CreateBuildingButton().ToSharedRef());
}
TSharedPtr<SWidget> MainViewUIController::CreateUserView()
{
	TSharedPtr<SVerticalBox> ResWidget = SNew(SVerticalBox)
		+SVerticalBox::Slot()
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Top)
		.Padding(32, 18, 0, 0)
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Center)
			[
				SNew(SBox)
				.WidthOverride(40)
				.HeightOverride(40)
				[
					SNew(SButton)
					.ButtonStyle(&FGameStyle::Get().GetWidgetStyle<FButtonStyle>("Button.Power"))
				]
			]
			+ SHorizontalBox::Slot()
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Center)
				.Padding(18, 0, 0, 0)
			[
				SNew(SBox)
				.WidthOverride(100)
				.HeightOverride(100)
				[
					SNew(SImage)
					.Image(FGameStyle::Get().GetBrush("Icon.Power"))
				]
			]
		];
	
	return ResWidget;
}
TSharedPtr<SWidget>	MainViewUIController::CreateToWorldButton()
{

	return SNullWidget::NullWidget;
}
TSharedPtr<SWidget>	MainViewUIController::CreateBuildingButton()
{

	return SNullWidget::NullWidget;
}

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
