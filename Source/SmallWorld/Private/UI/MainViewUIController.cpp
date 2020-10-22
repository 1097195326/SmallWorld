#include "MainViewUIController.h"
#include "SHordePowerWidget.h"
#include "SBuildingIconList.h"
#include "GameDataManager.h"
#include "SServiceDragDropWidget.h"
#include "UserGameInstance.h"
#include "UserController.h"
#include "UserViewportClient.h"
#include "GameMenuWidgetStyle.h"

MainViewUIController::MainViewUIController()
{
	

}
void MainViewUIController::InitControllerView()
{
	ControllerView->AddSlot(0)
		[
			SNew(SServiceDragDropWidget)
		];
	

}
void MainViewUIController::OnEnter()
{
	

}
void MainViewUIController::OnExit()
{
}
void MainViewUIController::SelectGameActor(AGameActor * GameActorPtr)
{
	if (GameActorPtr == nullptr)
	{
		return;
	}
	MiddleBottomSlot->AttachWidget(GameActorPtr->CreateActorDetailWidget().ToSharedRef());
	
}
void MainViewUIController::SelectHorde()
{

}

//// -----------------
//TSharedPtr<SWidget>	MainViewUIController::TestWidget()
//{
//	TSharedPtr<SImage> ShowImage = SNew(SImage);
//	FString  PackageName = TEXT("/Game/CastlePack/Meshes/SM_Mine_lvl0");
//	FString PackageFilename;
//	if (FPackageName::DoesPackageExist(PackageName, NULL, &PackageFilename))
//	{
//		FAssetData AssetData = FAutomationEditorCommonUtils::GetAssetDataFromPackagePath(PackageFilename);
//		FName ObjectFullName = FName(*AssetData.GetFullName());
//		
//		FThumbnailMap ThumbnailMap;
//
//		const FObjectThumbnail* ThumbnailPtr = ThumbnailTools::FindCachedThumbnail(ObjectFullName.ToString());
//		if (!ThumbnailPtr)
//		{
//			TSet<FName> ObjectFullNames;
//			ObjectFullNames.Add(ObjectFullName);
//			ThumbnailTools::LoadThumbnailsFromPackage(PackageFilename, ObjectFullNames, ThumbnailMap);
//			ThumbnailPtr = ThumbnailMap.Find(ObjectFullName);
//		}
//		if (ThumbnailPtr)
//		{
//			static TSharedPtr<FSlateDynamicImageBrush> DynamicBrush = FSlateDynamicImageBrush::CreateWithImageData(
//				ObjectFullName,
//				FVector2D(ThumbnailPtr->GetImageWidth(), ThumbnailPtr->GetImageHeight()),
//				ThumbnailPtr->GetUncompressedImageData());
//			if (DynamicBrush.IsValid() && ThumbnailPtr->GetUncompressedImageData().Num() > 0)
//			{
//				ShowImage->SetImage(DynamicBrush.Get());
//			}
//		}
//	}
//	return
//		SNew(SBox)
//		.WidthOverride(100)
//		.HeightOverride(100)
//		[
//			SNew(SBorder)
//			.Padding(0)
//			//.BorderBackgroundColor(FLinearColor(1,0,0,0.3f))
//			.BorderBackgroundColor(FGameStyle::Get().GetColor("Color.FFFFC266"))
//			.BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
//			[
//				ShowImage.ToSharedRef()
//			]
//		];
//	
//}
